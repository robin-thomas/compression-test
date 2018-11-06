#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <iomanip>

#include "minilzo.h"
#include "zlib.h"
#include "ucl.h"
#include "quicklz.h"
#include "snappy.h"

/*
 * Function to read the file data to compress/uncompress
 */
std::vector<unsigned char> get_data(std::string file) {
  std::ifstream in;
  in.open(file, std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "[ERROR]: Unable to open file " << file << std::endl;
    return {};
  }

  return { std::istream_iterator<unsigned char>(in), std::istream_iterator<unsigned char>() } ;
}


/*
 * Function to validate that the compressed and uncompressed data match
 */
bool match(unsigned char* src_buf, size_t src_size,
           unsigned char* dest_buf, size_t dest_size) {

  if (src_size != dest_size) {
    std::cerr << "size of original and uncompressed data do not match!" << std::endl;
    return false;
  }

  if (src_buf == nullptr || dest_buf == nullptr) {
    std::cerr << "Either one or all buffers are empty!" << std::endl;
    return false;
  }

  size_t i = 0;
  while (i < src_size && *(src_buf + i) == *(dest_buf + i)) {
    i++;
  }
  if (i != src_size)
    return false;

  std::cout << "Original and uncompressed data match!" << std::endl;
  return true;
}


int main(int argc, char **argv) {
  int ret = 0;
  unsigned char* compressed = nullptr;
  unsigned char* uncompressed = nullptr;

  size_t compressed_size = 0;
  size_t uncompressed_size = 0;

  std::vector<unsigned char> buf;

  int algo = -1;
  Zip *zip = nullptr;

  if (argc != 3) {
    std::cout << "Format: ./binary filename compress_algo[minilzo = 1, zlib = 2, ucl = 3, quicklz = 4, snappy = 5]" << std::endl;
    ret = 1;
    goto out;
  }

  // Read the file based on user input.
  buf = get_data(argv[1]);

  try {
    algo = std::stoi(argv[2]);
  } catch(std::exception const &e) {
    std::cerr << "[ERROR]: unable to parse the input compression method" << std::endl;
    ret = 1;
    goto out;
  }

  switch(algo) {
    case 1:
      zip = new Minilzo();
      break;
    case 2:
      zip = new Zlib();
      break;
    case 3:
      zip = new Ucl();
      break;
    case 4:
      zip = new Quicklz();
      break;
    case 5:
      zip = new Snappy();
      break;
  }
  if (zip == nullptr) {
    std::cerr << "[ERROR]: unrecognized compressoin method" << std::endl;
    ret = 1;
    goto out;
  }

  // Compress.
  compressed_size = buf.size();
  compressed = new unsigned char[2 * buf.size()];
  if (zip->zip(&buf[0], buf.size(), compressed, compressed_size) != 0) {
    std::cerr << "[ERROR]: unable to compress" << std::endl;
    ret = 1;
    goto out;
  }

  // Uncompress.
  uncompressed_size = buf.size();
  uncompressed = new unsigned char[buf.size()];
  if (zip->unzip(compressed, compressed_size, uncompressed, uncompressed_size) != 0) {
    std::cerr << "[ERROR]: unable to uncompress" << std::endl;
    ret = 1;
    goto out;
  }

  // Check that uncompressed and original data match.
  if (match(&buf[0], buf.size(), uncompressed, uncompressed_size) == false) {
    std::cerr << "[ERROR]: issue with compression/uncompress algo!" << std::endl;
    ret = 1;
    goto out;
  }
  if (buf.size() < compressed_size)
    goto out;

  // Calculate compression ratio.
  std::cout << "Compression rate: " << std::fixed << std::setprecision(2) << (100.0 * (buf.size() - compressed_size)) / buf.size() << "%" << std::endl;

out:
  if (buf.size())
    buf.clear();

  if (compressed)
    delete[] compressed;

  if (uncompressed)
    delete[] uncompressed;

  if (zip)
    delete zip;

  return ret;
}

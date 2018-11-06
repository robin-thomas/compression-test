#include <iostream>

#include "zip.h"
#include "snappy.h"
#include "snappy/snappy.h"

int Snappy::zip(unsigned char* src_buf, size_t src_size,
                unsigned char* dest_buf, size_t& dest_size) {
    if (src_size == 0 || src_buf == nullptr) {
      return -1;
    }

    std::string output;
    snappy::Compress((const char*)src_buf, src_size, &output);
    output.copy((char*)dest_buf, output.size());
    dest_buf[output.size()] = 0;
    dest_size = output.size();

    // This is one way of getting the size of the output
    std::cout << "Compressed size is: "<< dest_size << std::endl;

    return 0;
  }


int Snappy::unzip(unsigned char* src_buf, size_t src_size,
                  unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  std::string output;
  snappy::Uncompress((const char*)src_buf, src_size, &output);
  output.copy((char*)dest_buf, output.size());
  dest_buf[output.size()] = 0;
  dest_size = output.size();

  std::cout << "Uncompressed size is: " << dest_size << std::endl;

  return 0;
}

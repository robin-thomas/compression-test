#include <iostream>

#include "zip.h"
#include "lz4.h"
#include "lz4/lib/lz4.h"

int Lz4::zip(unsigned char* src_buf, size_t src_size,
             unsigned char* dest_buf, size_t& dest_size) {
    if (src_size == 0 || src_buf == nullptr) {
      return -1;
    }

    int r = LZ4_compress_default((const char*)src_buf, (char*)dest_buf, src_size, src_size * 2 - 1);
    if (r <= 0)
      return -1;

    dest_size = r;

    std::cout << "Compressed size is: "<< dest_size << std::endl;

    return 0;
  }


int Lz4::unzip(unsigned char* src_buf, size_t src_size,
               unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  int r = LZ4_decompress_safe((const char*)src_buf, (char*)dest_buf, src_size, src_size * 2 - 1);
  if (r <= 0)
    return -1;

  dest_size = r;

  std::cout << "Uncompressed size is: " << dest_size << std::endl;

  return 0;
}

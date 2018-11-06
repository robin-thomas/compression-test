#include <iostream>

#include "zip.h"
#include "quicklz.h"
#include "quicklz/quicklz.h"

int Quicklz::zip(unsigned char* src_buf, size_t src_size,
                 unsigned char* dest_buf, size_t& dest_size) {
    if (src_size == 0 || src_buf == nullptr) {
      return -1;
    }

    qlz_state_compress *state_compress = (qlz_state_compress *)malloc(sizeof(qlz_state_compress));

    dest_size = qlz_compress(src_buf, (char*)dest_buf, src_size, state_compress);

    // This is one way of getting the size of the output
    std::cout << "Compressed size is: "<< dest_size << std::endl;

    return 0;
  }


int Quicklz::unzip(unsigned char* src_buf, size_t src_size,
                   unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));

  dest_size = qlz_decompress((char*)src_buf, dest_buf, state_decompress);

  std::cout << "Uncompressed size is: " << dest_size << std::endl;

  return 0;
}

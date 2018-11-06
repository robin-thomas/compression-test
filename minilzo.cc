#include <iostream>

#include "zip.h"
#include "minilzo.h"
#include "minilzo/minilzo.h"

#define HEAP_ALLOC(var,size) \
      lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

int Minilzo::zip(unsigned char* src_buf, size_t src_size,
                 unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  if (lzo_init() != LZO_E_OK) {
    std::cerr << "internal error - lzo_init() failed !!!" << std::endl;
    std::cerr << "(this usually indicates a compiler bug - try recompiling without optimizations, and enable '-DLZO_DEBUG' for diagnostics)" << std::endl;
    return -2;
  }

  int r = lzo1x_1_compress(src_buf, src_size, dest_buf, &dest_size, wrkmem);
  if (r == LZO_E_OK) {
    std::cout << "compressed " << src_size << "bytes into " << dest_size << "bytes" << std:: endl;
  } else {
    /* this should NEVER happen */
    std::cerr << "internal error - compression failed: " << r << std::endl;
    return -3;
  }

  /* check for an incompressible block */
  if (dest_size >= src_size) {
    std::cerr << "This block contains incompressible data." << std::endl;
  }

  return 0;
}

int Minilzo::unzip(unsigned char* src_buf, size_t src_size,
                   unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  int r = lzo1x_decompress(src_buf, src_size, dest_buf, &dest_size, NULL);
  if (r == LZO_E_OK) {
    std::cout << "decompressed " << src_size << " bytes back into " << dest_size << " bytes" << std::endl;
  } else {
    /* this should NEVER happen */
    std::cerr << "internal error - decompression failed: " << r << std::endl;
    return -2;
  }

  return 0;
}

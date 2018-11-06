#include <iostream>

#include "zip.h"
#include "ucl.h"

#include "ucl/ucl.h"
#if defined(UCL_USE_ASM)
#  include "ucl/ucl_asm.h"
#endif

int Ucl::zip(unsigned char* src_buf, size_t src_size,
             unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  if (ucl_init() != UCL_E_OK) {
    std::cerr << "internal error - ucl_init() failed !!!" << std::endl;
    std::cerr << "(this usually indicates a compiler bug - try recompiling without optimizations, and enable '-DLZO_DEBUG' for diagnostics)" << std::endl;
    return -2;
  }

  int level = 10;
  int r = ucl_nrv2b_99_compress(src_buf, src_size, dest_buf, (ucl_uint*)&dest_size, NULL, level, NULL, NULL);
  if (r == UCL_E_OK) {
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

int Ucl::unzip(unsigned char* src_buf, size_t src_size,
               unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  #if defined(UCL_USE_ASM)
  int r = ucl_nrv2b_decompress_asm_8(src_buf, src_size, dest_buf, (ucl_uint*)&dest_size, NULL);
  #else
  int r = ucl_nrv2b_decompress_8(src_buf, src_size, dest_buf, (ucl_uint*)&dest_size, NULL);
  #endif

  if (r == UCL_E_OK) {
    std::cout << "decompressed " << src_size << " bytes back into " << dest_size << " bytes" << std::endl;
  } else {
    /* this should NEVER happen */
    std::cerr << "internal error - decompression failed: " << r << std::endl;
    return -2;
  }

  return 0;
}

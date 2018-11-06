#ifndef ZLIB_H__
#define ZLIB_H__

#include <iostream>
#include <cstdlib>

#include "zip.h"

class Zlib : public Zip {
public:
  Zlib() {
    std::cout << "Using ZLIB algo" << std::endl;
  }

  int zip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
  int unzip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
};

#endif // ZLIB_H__

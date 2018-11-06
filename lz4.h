#ifndef LZ4_H__
#define LZ4_H__

#include <iostream>
#include <cstdlib>

#include "zip.h"

class Lz4 : public Zip {
public:
  Lz4() {
    std::cout << "Using Lz4 algo" << std::endl;
  }

  int zip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
  int unzip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
};

#endif // Lz4_H__

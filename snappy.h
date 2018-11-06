#ifndef SNAPPY_H__
#define SNAPPY_H__

#include <iostream>
#include <cstdlib>

#include "zip.h"

class Snappy : public Zip {
public:
  Snappy() {
    std::cout << "Using SNAPPY algo" << std::endl;
  }

  int zip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
  int unzip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
};

#endif // SNAPPY_H__

#ifndef QUICKLZ_H__
#define QUICKLZ_H__

#include <iostream>
#include <cstdlib>

#include "zip.h"

class Quicklz : public Zip {
public:
  Quicklz() {
    std::cout << "Using QUICKLZ algo" << std::endl;
  }

  int zip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
  int unzip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
};

#endif // QUICKLZ_H__

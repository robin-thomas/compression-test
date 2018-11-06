#ifndef UCL_H__
#define UCL_H__

#include <iostream>
#include <cstdlib>

#include "zip.h"

class Ucl : public Zip {
public:
  Ucl() {
    std::cout << "Using UCL algo" << std::endl;
  }

  int zip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
  int unzip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
};

#endif // UCL_H__

#ifndef MINILZO_H__
#define MINILZO_H__

#include <iostream>
#include <cstdlib>

#include "zip.h"

class Minilzo : public Zip {
public:
  Minilzo() {
    std::cout << "Using MINILZO algo" << std::endl;
  }

  int zip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
  int unzip(unsigned char* src_buf, size_t src_size, unsigned char* dest_buf, size_t& dest_size);
};

#endif // MINILZO_H__

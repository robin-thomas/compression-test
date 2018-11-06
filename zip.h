#ifndef ZIP_H__
#define ZIP_H__

#include <cstdlib>

class Zip {
public:
  virtual int zip(unsigned char* in, size_t in_len, unsigned char* out, size_t& out_len) = 0;
  virtual int unzip(unsigned char* in, size_t in_len, unsigned char* out, size_t& out_len) = 0;

  virtual ~Zip(){}
};

#endif // ZIP_H__
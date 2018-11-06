#include <iostream>

#include "zip.h"
#include "zlib.h"
#include "zlib/zlib.h"

int Zlib::zip(unsigned char* src_buf, size_t src_size,
              unsigned char* dest_buf, size_t& dest_size) {
    if (src_size == 0 || src_buf == nullptr) {
      return -1;
    }

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = src_size + 1; // size of input string + terminator
    defstream.next_in = (Bytef *)src_buf; // input char array
    defstream.avail_out = dest_size; // size of output
    defstream.next_out = (Bytef *)dest_buf; // output char array

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);
    dest_size = defstream.total_out;

    // This is one way of getting the size of the output
    std::cout << "Compressed size is: "<< dest_size << std::endl;

    return 0;
  }


int Zlib::unzip(unsigned char* src_buf, size_t src_size,
                     unsigned char* dest_buf, size_t& dest_size) {
  if (src_size == 0 || src_buf == nullptr) {
    return -1;
  }

  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;

  infstream.avail_in = src_size + 1; // size of input
  infstream.next_in = (Bytef *)src_buf; // input char array
  infstream.avail_out = dest_size; // size of output
  infstream.next_out = (Bytef *)dest_buf; // output char array

  inflateInit(&infstream);
  inflate(&infstream, Z_NO_FLUSH);
  inflateEnd(&infstream);
  dest_size = infstream.total_out;

  std::cout << "Uncompressed size is: " << dest_size << std::endl;

  return 0;
}

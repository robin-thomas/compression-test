#!/bin/sh

cd ./lib/zlib && make && cd ../..
cd ./lib/ucl && ./configure && make && cd ../..
cd ./lib/lzma/CPP/7zip/Bundles/LzmaCon && make -f makefile.gcc clean all && cd ../../../../../..
cd ./lib/snappy && cmake . && make && cd ../..
cd ./lib/lz4 && make && cd ../..

g++ main.cc zlib.cc minilzo.cc ucl.cc quicklz.cc snappy.cc lz4.cc -o main \
  ./lib/minilzo/minilzo.c ./lib/quicklz/quicklz.c \
  -g -std=c++11 -Wall \
  -I./lib -I./lib/ucl/include \
  -L./lib/ucl/src/.libs -L./lib/lz4/lib/ \
  -llz4 -lsnappy -lucl -lz

#!/bin/sh

cd ./lib/zlib && make && cd ../..
cd ./lib/ucl && ./configure && make && cd ../..
cd ./lib/lzma/CPP/7zip/Bundles/LzmaCon && make -f makefile.gcc clean all && cd ../../../../../..
cd ./lib/snappy && cmake . && make && cd ../..

g++ main.cc zlib.cc minilzo.cc ucl.cc quicklz.cc snappy.cc ./lib/minilzo/minilzo.c ./lib/quicklz/quicklz.c -g -std=c++11 -I./lib -I./lib/ucl/include -L./lib/ucl/src/.libs -lsnappy -lucl -lz -Wall -o main

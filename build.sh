#!/bin/sh

cd ./lib/zlib && make && cd ../..

g++ main.cc zlib.cc minilzo.cc ./lib/minilzo/minilzo.c -g -std=c++11 -I./lib -lz -Wall -o main

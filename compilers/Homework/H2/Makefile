CC = g++
CFLAGS := -g -std=c++11

all: compiler
compiler: compiler.h compiler.cc test.cc
	$(CC) $(CFLAGS) test.cc compiler.cc -o test 

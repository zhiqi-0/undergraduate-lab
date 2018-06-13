CXX = g++

all: dblock

dblock: dblock.h lzq.h dblock.cc test.cc
	$(CXX) -std=c++14 -O3 test.cc dblock.cc -o dblock

clean:
	rm -f dblock
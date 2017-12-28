CXX = g++

all: random_gen mulmatrix

random_gen: randomdata.cc lzq.h
	$(CXX) -std=c++14 -O3 randomdata.cc -o data_gen

mulmatrix: mulmatrix.cc lzq.h
	$(CXX) -std=c++14 -O3 mulmatrix.cc -o mulmatrix

clean:
	rm -f data_gen mulmatrix
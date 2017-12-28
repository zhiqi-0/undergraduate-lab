CXX = g++

all: random_gen fft_mul norm_mul

random_gen: randomdata.cc lzq.h
	$(CXX) -std=c++14 -O3 randomdata.cc -o data_gen

fft_mul: fftmul.cc lzq.h
	$(CXX) -std=c++14 -O3 fftmul.cc -o fft

norm_mul: normmul.cc lzq.h
	$(CXX) -std=c++14 -O3 normmul.cc -o norm 

clean:
	rm -f fft data_gen norm
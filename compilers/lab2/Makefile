all: gen_fib
gen_fib: gen_fib.cpp
	c++ `llvm-config --cxxflags --ldflags --system-libs --libs` gen_fib.cpp -o gen_fib
	
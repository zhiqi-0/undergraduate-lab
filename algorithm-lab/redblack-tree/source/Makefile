CXX = g++

all: datagen rbtree test check

datagen: datagen.cc lzq.h
	$(CXX) -std=c++14 -O3 -g datagen.cc -o datagen

rbtree: lzq.h rbtree.cc redblacktree.h
	$(CXX) -std=c++14 -O3 -g rbtree.cc -o rbtree

test: test.cc redblacktree.h
	$(CXX) -std=c++14 -O3 -g test.cc -o test

check: select.cc
	$(CXX) -std=c++14 -O3 -g select.cc -o check

clean:
	rm -rf *.dSYM
	rm check datagen rbtree test 
CXX = g++

all: datagen graph

datagen: datagen.cc lzq.h
	$(CXX) -std=c++14 -O3 datagen.cc -o datagen

graph: graph.h test.cc lzq.h
	$(CXX) -std=c++14 -O3 test.cc -o graph

clean:
	rm -f datagen
	rm -f graph
	rm -f ../output/size*/*
	rm -f ../output/*.gv
	rm -f ../output/*.png
	rm -f ../output/*.svg
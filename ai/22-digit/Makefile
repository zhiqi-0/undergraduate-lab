$(CXX) = g++

all: Ah1 IDAh1 Ah2 IDAh2

Ah1: Ah1.cpp
	$(CXX) -O3 Ah1.cpp -o Ah1

Ah2: Ah2.cpp
	$(CXX) -O3 Ah2.cpp -o Ah2

IDAh1: IDAh1.cpp
	$(CXX) -O3 -std=c++11 IDAh1.cpp -o IDAh1

IDAh2: IDAh2.cpp
	$(CXX) -O3 -std=c++11 IDAh2.cpp -o IDAh2

clean:
	rm Ah1 IDAh1 IDAh2 Ah2
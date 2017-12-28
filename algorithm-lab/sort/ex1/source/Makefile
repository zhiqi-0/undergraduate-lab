all: gen sortalg
gen: randomdata.cc lzq.h
	g++ -std=c++11 randomdata.cc -o gen
sortalg: test.cc sort.h lzq.h
	g++ -std=c++11 test.cc -DProgressBar -o sort
clean:
	rm -f gen sort
	find .. -type f -name 'result*' -exec rm -rf {} \;
	find .. -type f -name 'time.txt' -exec rm -rf {} \;
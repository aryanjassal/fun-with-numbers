run: build
	./fun_with_numbers.o

build:
	g++ fun_with_numbers.cpp -o fun_with_numbers.o -static -Ofast -Wl,-u,pthread_join

algo:
	g++ factors_algo.cpp -o factors_algo.o
	./factors_algo.o

clean:
	rm fun_with_numbers.o

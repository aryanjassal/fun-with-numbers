run: build
	.build/fun_with_numbers.o

build:
	g++ src/fun_with_numbers.cpp -o build/fun_with_numbers.o -static -Ofast -Wl,-u,pthread_join

algo:
	g++ src/factors_algo.cpp -o build/factors_algo.o
	./factors_algo.o

clean:
	rm **/*.o

make todo:
	grep -i -R "todo" . --exclude=Makefile

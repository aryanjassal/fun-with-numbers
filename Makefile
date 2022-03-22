.PHONY: run build algo clean todo

run: build
	.build/fun_with_numbers.o

build:
	mkdir -p build
	g++ src/fun_with_numbers.cpp -o build/fun_with_numbers.o -static -Ofast -lncurses,-Wl,-u,pthread_join

algo:
	g++ src/factors_algo.cpp -o build/factors_algo.o
	.build/factors_algo.o

clean:
	rm **/*.o

todo:
	grep -i -R "todo" . --exclude=Makefile

plot:
	mkdir -p build
	g++ src/plot_numbers.cpp -o build/plot_numbers.o -lncurses -Wall -g
	./build/plot_numbers.o

# -static -Ofast

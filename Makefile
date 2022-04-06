.PHONY: run build exec

run: build
	./build/fun_with_numbers.o

build:
	mkdir -p build
	g++ -Ofast -lncurses -Wall -I./include src/main.cpp src/utils.cpp -o build/fun_with_numbers.o

exec:
	./build/fun_with_numbers.o
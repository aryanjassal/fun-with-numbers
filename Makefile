#* Makefile confuses recipies with directory names. PHONY ensures that it doesn't happen and only the recipies are executed
.PHONY: run build exec

#* Build the file first and then run the output file
#* The first recipie is executed when the command `make` is executed. All other commands are executed using the command `make <recipie>`
run: build
	./build/fun_with_numbers.o

#* The recipie to build the code by first making a build directory then compiling the code using g++
build:
	mkdir -p build
	g++ -Ofast -lncurses -Wall -I./include src/*.cpp -o build/fun_with_numbers.o

#* Execute only the output only. To execute the compiled output file using build recipie
exec:
	./build/fun_with_numbers.o
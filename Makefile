build:
	g++ fun_with_numbers.cpp  -lao -ldl -lm -o fun_with_numbers.o -static -Ofast -Wl,-u,pthread_join

run: build
	./fun_with_numbers.o

clean:
	rm fun_with_numbers.o

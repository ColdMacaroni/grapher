grapher: main.o
	clang -o grapher main.o -lm

main.o: main.c points.h
	clang -Wall -Wextra -pedantic -c main.c

clean:
	rm grapher main.o

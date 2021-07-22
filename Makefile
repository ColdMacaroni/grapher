grapher: main.o
	clang -o grapher main.o -lm

main.o:
	clang -Wall -Wextra -pedantic -c main.c

clean:
	rm grapher main.o

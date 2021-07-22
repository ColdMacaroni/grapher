grapher: main.o
	clang -o grapher main.o

main.o:
	clang -Wall -Wextra -pedantic -c main.c -lm

clean:
	rm grapher main.o

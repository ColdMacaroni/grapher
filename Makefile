grapher:
	clang -Wall -Wextra -pedantic -o grapher grapher.c -lm

clean:
	rm grapher

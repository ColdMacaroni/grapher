grapher: main.o writepbm.o
	clang -o grapher main.o writepbm.o -lm

main.o: main.c points.h writepbm.h
	clang -Wall -Wextra -pedantic -c main.c

writepbm.o: points.h
	clang -Wall -Wextra -pedantic -c writepbm.c

clean:
	rm grapher main.o writepbm.o

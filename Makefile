grapher: main.o writepbm.o points.o
	clang -o grapher main.o writepbm.o points.o -lm

main.o: main.c points.h writepbm.h
	clang -Wall -Wextra -pedantic -c main.c

writepbm.o: writepbm.c points.h
	clang -Wall -Wextra -pedantic -c writepbm.c

points.o: points.c points.h
	clang -Wall -Wextra -pedantic -c points.c

clean:
	rm grapher main.o writepbm.o points.o

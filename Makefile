#-*-Makefile-*-

#target: dependencies
#	action (CLI instruction to build dependency)

all: parse

parse: parse.o parselib.o
	gcc parse.o parselib.o -o parse -lm
	rm *.o

parse.o: parse.c parselib.h
	gcc -c parse.c

parselib.o: parselib.c parselib.h
	gcc -c parselib.c

clean:
	rm *.o parse
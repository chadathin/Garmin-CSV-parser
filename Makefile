#-*-Makefile-*-

#target: dependencies
#	action (CLI instruction to build dependency)

all: parse

parse: parse.o parselib.o actstr.o
	gcc parse.o parselib.o actstr.o -o parse -g -lm
	rm *.o

parse.o: parse.c 
	gcc -c -g parse.c

parselib.o: parselib.c parselib.h actstr.h
	gcc -c parselib.c

actstr.o: actstr.c actstr.h parselib.h
	gcc -c actstr.c

clean:
	rm *.o parse
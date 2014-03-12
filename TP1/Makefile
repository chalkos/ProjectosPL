.PHONY: all clean

CC=gcc -Wall
FLEX=flex

all: parser

parser: lex.yy.o
	$(CC) lex.yy.o -ll -o $@

lex.yy.c: flex.l
	flex flex.l

lex.yy.o: lex.yy.c
	$(CC) -c -ll lex.yy.c

clean:
	$(RM) *.o
	$(RM) parser

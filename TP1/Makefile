.PHONY: all clean

CC=gcc -Wall
FLEX=flex

all: parser

parser: lex.yy.o hlink.o 
	$(CC) $^ -ll -o $@

lex.yy.c: parser.l
	flex parser.l

lex.yy.o: lex.yy.c
	$(CC) -c -ll lex.yy.c

hlink.o: hlink.c
	$(CC) -c hlink.c

clean:
	$(RM) lex.yy.c
	$(RM) *.o
	$(RM) parser

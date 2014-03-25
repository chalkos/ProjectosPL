.PHONY: all clean

CC=gcc -Wall
FLEX=flex

all: parser

parser: lex.yy.o hlink.o pagina.o
	$(CC) $^ -ll -o $@

lex.yy.c: parser.l
	flex parser.l

lex.yy.o: lex.yy.c
	$(CC) -c -ll lex.yy.c

hlink.o: hlink.c hlink.h
	$(CC) -c hlink.c

pagina.o: pagina.c pagina.h
	$(CC) -c pagina.c

clean:
	$(RM) lex.yy.c
	$(RM) *.o
	$(RM) parser

.PHONY: all clean

CC=gcc -Wall
FLEX=flex

all: parser

parser: lex.yy.o ilink.o pagina.o
	$(CC) $^ -ll -o $@

lex.yy.c: parser.l
	flex parser.l

lex.yy.o: lex.yy.c
	$(CC) -c -ll lex.yy.c

ilink.o: ilink.c ilink.h
	$(CC) -c ilink.c

pagina.o: pagina.c pagina.h
	$(CC) -c pagina.c

elementos.o: elementos.c elementos.h
	$(CC) -c elementos.c

clean:
	$(RM) lex.yy.c
	$(RM) *.o
	$(RM) parser

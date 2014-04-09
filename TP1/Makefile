.PHONY: all clean

CC=gcc -Wall -g
FLEX=flex

all: nawp

nawp: lex.yy.o ilink.o hlink.o pagina.o paginas.o seccao.o
	$(CC) $^ -ll -o $@

lex.yy.c: nawp.l
	$(FLEX) nawp.l

lex.yy.o: lex.yy.c 
	$(CC) -c -ll lex.yy.c

ilink.o: ilink.c ilink.h
	$(CC) -c ilink.c

paginas.o: paginas.c paginas.h
	$(CC) -c paginas.c

pagina.o: pagina.c pagina.h
	$(CC) -c pagina.c

seccao.o: seccao.c seccao.h
	$(CC) -c seccao.c

hlink.o: hlink.c hlink.h
	$(CC) -c hlink.c

clean:
	$(RM) lex.yy.c
	$(RM) *.o
	$(RM) nawp

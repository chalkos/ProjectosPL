arvore : y.tab.o arv.lib.o lex.yy.o
	gcc -Wall -g -o $@ $^ -ll

arv.lib.o : arv.lib.c arv.lib.h
	gcc -c arv.lib.c

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

y.tab.c y.tab.h : arv.y arv.lib.h
	yacc -d arv.y

lex.yy.o : lex.yy.c arv.lib.h
	gcc -c lex.yy.c

lex.yy.c : arv.l y.tab.h arv.lib.h
	flex arv.l

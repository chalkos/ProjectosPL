.PHONY: clean

ag : y.tab.o lex.yy.o
	gcc -o ag y.tab.o lex.yy.o -ll

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h y.tab.c : agenda.y
	yacc agenda.y

lex.yy.c : agenda.l
	flex agenda.l

clean :
	rm -rf *.o ag

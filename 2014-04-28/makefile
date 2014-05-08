calc: lex.yy.o y.tab.o
	gcc -o calc lex.yy.o y.tab.o -ll -ly

lex.yy.o : lex.yy.c
	gcc -c lex.yy.c

lex.yy.c : y.tab.h calc.l
	flex calc.l

y.tab.o : y.tab.c y.tab.h
	gcc -c y.tab.c

y.tab.c y.tab.h : calc.y
	yacc -d calc.y

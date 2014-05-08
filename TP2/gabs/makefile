SUF=dummy

gabs: parser.o lex.yy.o gabsGA.o gabsSEM.o gabsCODE.o
	cc -o gabs parser.o gabsGA.o gabsSEM.o gabsCODE.o lex.yy.o -ll 
	rm lex.yy.*

parser.o: parser.c tokens.h gabsGA.h gabsSEM.h gabsCODE.h
	cc -c parser.c

lex.yy.o: lex.yy.c 
	cc -c lex.yy.c

lex.yy.c: gabs.l tokens.h
	flex -l gabs.l

gabsGA.o: gabsGA.c gabsGA.h
	cc -c gabsGA.c

gabsSEM.o: gabsSEM.c gabsSEM.h
	cc -c gabsSEM.c

gabsCODE.o: gabsCODE.c gabsCODE.h
	cc -c gabsCODE.c

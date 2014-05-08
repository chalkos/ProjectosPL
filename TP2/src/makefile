.PHONY: clean

cmdtok : cmd.tok.c lex.cmd.o cmd.tab.o cmd.lib.o
	gcc -o $@ $^ -ll

cmd : cmd.lib.o lex.cmd.o cmd.tab.o
	gcc -o $@ $^ -ll

cmd.lib.o : cmd.lib.c cmd.lib.h
	gcc -c cmd.lib.c

cmd.tab.o : cmd.tab.h cmd.tab.c
	gcc -c cmd.tab.c

lex.cmd.o : lex.cmd.c cmd.tab.h
	gcc -c lex.cmd.c -ll

cmd.tab.c cmd.tab.h : cmd.y cmd.lib.h
	yacc -d -pcmd -bcmd cmd.y

lex.cmd.c : cmd.l
	flex -Pcmd cmd.l

clean :
	$(RM) gabs
	$(RM) *.o
	$(RM) *.tab.[ch]
	$(RM) lex.*.c

gabs:
	cd ./../gabs/ && $(MAKE) gabs && mv ./gabs ./../src/gabs


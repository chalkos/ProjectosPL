.PHONY: clean


#----------------\
#  Tokens        \
#----------------´

cmdtok : cmd.tok.c lex.cmd.o cmd.tab.o cmd.lib.o
	gcc -o $@ $^ -ll

#----------------\
#  Cfg           \
#----------------´

cfg : cfg.lib.o lex.cfg.o cfg.tab.o
	gcc -o $@ $^ -ll

cfg.lib.o : cfg.lib.c cfg.lib.h
	gcc -c cfg.lib.c

cfg.tab.o : cfg.tab.h cfg.tab.c
	gcc -c cfg.tab.c

lex.cfg.o : lex.cfg.c cfg.tab.h cfg.lib.o
	gcc -c lex.cfg.c -ll

cfg.tab.c cfg.tab.h : cfg.y cfg.lib.o
	yacc -d -pcfg -bcfg cfg.y

lex.cfg.c : cfg.l
	flex -Pcfg cfg.l

#----------------\
#  Cmd           \
#----------------´

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

#----------------\
#  Extras        \
#----------------´

clean :
	$(RM) gabs
	$(RM) cmd
	$(RM) cfg
	$(RM) *.o
	$(RM) *.tab.[ch]
	$(RM) lex.*.c

gabs:
	cd ./../gabs/ && $(MAKE) gabs && mv ./gabs ./../src/gabs


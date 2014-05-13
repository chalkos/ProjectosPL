.PHONY: clean

GDB=-g

#----------------\
#  Tokenizers    \
#----------------´

cmdtok : cmd.tok.c lex.cmd.o cmd.tab.o cmd.lib.o
	gcc $(GDB) -o $@ $^ -ll

cfgtok : cfg.tok.c lex.cfg.o cfg.tab.o cfg.lib.o
	gcc $(GDB) -o $@ $^ -ll

#----------------\
#  Gco           \
#----------------´

gco : gco.lib.c cfg.lib.o lex.cfg.o cfg.tab.o cmd.lib.o lex.cmd.o cmd.tab.o
	gcc $(GDB) -o $@ $^

#----------------\
#  Cfg           \
#----------------´

cfg : cfg.main.c cfg.lib.o lex.cfg.o cfg.tab.o
	gcc $(GDB) -o $@ $^ -ll

cfg.lib.o : cfg.lib.c cfg.lib.h
	gcc $(GDB) -c cfg.lib.c

cfg.tab.o : cfg.tab.h cfg.tab.c
	gcc $(GDB) -c cfg.tab.c

lex.cfg.o : lex.cfg.c cfg.tab.h cfg.lib.o
	gcc $(GDB) -c lex.cfg.c -ll

cfg.tab.c cfg.tab.h : cfg.y cfg.lib.o
	yacc -d -pcfg -bcfg cfg.y

lex.cfg.c : cfg.l
	flex -Pcfg cfg.l

#----------------\
#  Cmd           \
#----------------´

cmd : cmd.main.c cmd.lib.o lex.cmd.o cmd.tab.o
	gcc $(GDB) -o $@ $^ -ll

cmd.lib.o : cmd.lib.c cmd.lib.h
	gcc $(GDB) -c cmd.lib.c

cmd.tab.o : cmd.tab.h cmd.tab.c
	gcc $(GDB) -c cmd.tab.c

lex.cmd.o : lex.cmd.c cmd.tab.h
	gcc $(GDB) -c lex.cmd.c -ll

cmd.tab.c cmd.tab.h : cmd.y cmd.lib.h
	yacc -d -pcmd -bcmd cmd.y

lex.cmd.c : cmd.l
	flex -Pcmd cmd.l

#----------------\
#  Extras        \
#----------------´

clean :
	$(RM) gabs
	$(RM) gco
	$(RM) cmd
	$(RM) cfg
	$(RM) *.o
	$(RM) *.tab.[ch]
	$(RM) lex.*.c
	$(RM) *tok

gabs:
	cd ./../gabs/ && $(MAKE) gabs && mv ./gabs ./../src/gabs


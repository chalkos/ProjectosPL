.PHONY: clean

GDB=-g

#----------------\
#  Tokens        \
#----------------´

cmdtok : cmd.tok.c lex.cmd.o cmd.tab.o cmd.lib.o
	gcc $(GDB) -o $@ $^ -ll

#----------------\
#  Cfg           \
#----------------´

cfg : cfg.lib.o lex.cfg.o cfg.tab.o
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

cmd : cmd.lib.o lex.cmd.o cmd.tab.o
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
#  CsV          \
#----------------´

csv : csv.lib.o lex.csv.o csv.tab.o
	gcc $(GDB) -o $@ $^ -ll

csv.lib.o : csv.lib.c csv.lib.h
	gcc $(GDB) -c csv.lib.c

csv.tab.o : csv.tab.h csv.tab.c
	gcc $(GDB) -c csv.tab.c

lex.csv.o : lex.csv.c csv.tab.h
	gcc $(GDB) -c lex.csv.c -ll

csv.tab.c csv.tab.h : csv.y csv.lib.h
	yacc -d -pcsv -bcsv csv.y

lex.csv.c : csv.l
	flex -Pcsv csv.l
#----------------\
#  Extras        \
#----------------´

clean :
	$(RM) gabs
	$(RM) cmd
	$(RM) cfg
	$(RM) csv
	$(RM) *.o
	$(RM) *.tab.[ch]
	$(RM) lex.*.c

gabs:
	cd ./../gabs/ && $(MAKE) gabs && mv ./gabs ./../src/gabs


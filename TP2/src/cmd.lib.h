#ifndef __CMD_LIB_H
#define __CMD_LIB_H

#include <stdlib.h>

#include "csv.lib.h"

#define CMD_PROMPT "> "

typedef struct sLcsv {
    struct sLcsv *next;
    Linhas csv;
} *Lcsv;

Lcsv ListaCSV = NULL;

void cmd_config(char* ficheiro);
void cmd_load(char* ficheiro);
void cmd_import(char* ficheiro);
void cmd_print();
void cmd_save(char* ficheiro, int force);
void cmd_quit(int force);

#endif

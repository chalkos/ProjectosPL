#ifndef __CMD_LIB_H
#define __CMD_LIB_H

#include <stdlib.h>

#define CMD_PROMPT "> "

// carrega uma nova configuração
void cmd_config(char* ficheiro);

// carrega o estado da aplicação
void cmd_load(char* ficheiro);

// importa um CSV
void cmd_import(char* ficheiro);

// escreve o html com os dados existentes
void cmd_print();

// guarda o estado da aplicação
void cmd_save(char* ficheiro, int force);

// sair da aplicação
int cmd_quit();

#endif

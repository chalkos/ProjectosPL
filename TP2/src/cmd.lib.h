#ifndef __CMD_LIB_H
#define __CMD_LIB_H

#define CMD_PROMPT "> "

void cmd_config(char* ficheiro);
void cmd_load(char* ficheiro);
void cmd_import(char* ficheiro);
void cmd_print();
void cmd_save(char* ficheiro, int force);
void cmd_quit(int force);

#endif

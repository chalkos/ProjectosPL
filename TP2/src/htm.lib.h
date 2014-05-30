#ifndef __HTM_LIB_H
#define __HTM_LIB_H

#include "atl.lib.h"
#include "cfg.lib.h"
#include "csv.lib.h"

// escreve a parte da lista de provas e o nome do campeonato
void htm_print_indice( Confs cfg );

// escreve a parte inicial que é sempre igual
void htm_print_header();

int htm_begin();
void htm_end();

#endif

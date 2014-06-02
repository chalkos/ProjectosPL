#ifndef __SAV_LIB_H
#define __SAV_LIB_H

#include <stdio.h>

extern int sav_has_changes;
extern int sav_loading;

void sav_save(char* nome, int force);
void sav_load(char* nome);

#endif

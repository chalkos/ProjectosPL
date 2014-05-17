#ifndef __CMD_DUMMY_H
#define __CMD_DUMMY_H

#include <stdio.h>

int cfgparse();
void cfgset_in(FILE * in_str);
void cfglex_destroy();

int csvparse();
void csvset_in(FILE * in_str);
void csvlex_destroy();

#endif

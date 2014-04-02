#ifndef __PAGINAS_H
#define __PAGINAS_H

#include "pagina.h"

Elemento *paginas_create();
void paginas_add(Elemento* ps, Pagina* p);
void paginas_destroy(Elemento** paginas);
void paginas_print(Elemento* paginas);

#endif

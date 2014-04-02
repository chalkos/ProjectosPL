#ifndef __PAGINAS_H
#define __PAGINAS_H

#include "pagina.h"

Elemento* paginas_create();
void paginas_add(Pagina* pagina);
void paginas_destroy(Elemento** paginas);

#endif

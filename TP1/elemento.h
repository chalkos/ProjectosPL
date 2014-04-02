#ifndef __ELEMENTO_H
#define __ELEMENTO_H

#include "pagina.h"

typedef enum { TIPO_HLINK // hyperlink
             , TIPO_ILINK // internal link
             , TIPO_H1 // header 1
             , TIPO_H2 // header 2
             , TIPO_H3 // header 3
             , TIPO_H4 // header 4
             , TIPO_H5 // header 5
             , TIPO_H6 // header 6

             , TIPO_PAGINA // uma pagina
} Tipo;

typedef struct sElemento {
    Tipo tipo;
    void *dados;
    struct sElemento* proximo; // o proximo elemento
} Elemento;




// inserir um ILink
void elemento_add_ilink(Pagina* pagina, ILink* linkinfo);

#endif

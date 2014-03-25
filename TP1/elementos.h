#include "ilink.h"

typedef enum { TIPO_HLINK // hyperlink
             , TIPO_ILINK // internal link
             , TIPO_NEGRITO // negrito
             , TIPO_ITALICO // italico
             , TIPO_STRING // texto simples
} Tipo;

typedef struct sElemento {
    Tipo tipo;
    void *dados;
    struct sElemento* proximo; // o proximo elemento
    struct sElemento* filho; // o sub-elemento
    struct sElemento* pai; // o elemento pai
} Elemento;

void elemento_add_ilink(ILink* linkinfo);

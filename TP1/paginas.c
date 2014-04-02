#include "pagina.h"

#include <stdlib.h>

Elemento* paginas_create(){
    Elemento* paginas = (Elemento*) malloc(sizeof(Elemento));

    paginas->proximo = NULL;
    paginas->dados = NULL;
    paginas->tipo = TIPO_PAGINA;
}

void paginas_add(Pagina* pagina){

}

void paginas_destroy(Elemento** paginas){

}

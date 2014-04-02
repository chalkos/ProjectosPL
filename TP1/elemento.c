#include "elemento.h"
#include <stdlib.h>


void elemento_add_ilink(Pagina* pagina, ILink* linkinfo){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = linkinfo;
    e->proximo= NULL;
    e->tipo = TIPO_ILINK;

    Elemento* itr = pagina->iLinks;

    if( itr == NULL ){
        pagina->iLinks = e;
        return;
    }

    
}

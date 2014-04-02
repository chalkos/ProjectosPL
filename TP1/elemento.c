#include "elemento.h"
#include <stdlib.h>


void elemento_add_ilink(Pagina* pagina, ILink* linkinfo){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = linkinfo;
    e->proximo= NULL;
    e->tipo = TIPO_ILINK;

    Elemento* itr = pagina->iLinks;
    
    // se ainda nao houver elementos na lista
    if( itr == NULL ){
        pagina->iLinks = e;
        return;
    }
    
    // se ja houver elementos, percorrer até ao ultimo e inserir
    while( itr->proximo != NULL )
        itr = itr->proximo;

    itr->proximo = e;
}

void elemento_add_seccao(Pagina* pagina, Seccao* seccao){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = seccao;
    e->proximo= NULL;
    e->tipo = TIPO_HEADER;

    Elemento* itr = pagina->seccoes;
    
    // se ainda nao houver elementos na lista
    if( itr == NULL ){
        pagina->seccoes = e;
        return;
    }
    
    // se ja houver elementos, percorrer até ao ultimo e inserir
    while( itr->proximo != NULL )
        itr = itr->proximo;

    itr->proximo = e;
}

#include "pagina.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -1 se str1 <  str2
//  0 se str1 == str2
// +1 se str1 >  str2
int myStrCmp( char* str1, char* str2 ){
    if( !str1 && !str2 )
        return 0;
    
    if( !str1 && str2)
        return -1;
    
    if( str1 && !str2)
        return 1;
    

    //percorrer todos os iguais
    while(*str1 == *str2 && *str1 != '\0' && *str2 != '\0'){
        str1++;
        str2++;
    }
    
    if( *str1 < *str2 )
        return -1;
    
    if( *str1 > *str2 )
        return 1;
    

    // caso em que são iguais
    return 0;
}

void printTitulos(Elemento* ps){
    Elemento* itr = ps;
    
    // ordenado pelo titulo
    fprintf(stderr, "PS: ");
    while( itr ){
        fprintf(stderr, "%s -> ", ((Pagina*)(itr->dados))->titulo);
        itr = itr->proximo;
    }
    fprintf(stderr, "\n");
}

Elemento* paginas_create(){
    Elemento* paginas = (Elemento*) malloc(sizeof(Elemento));

    paginas->proximo = NULL;
    paginas->dados = NULL;

    return paginas;
}

void paginas_add(Elemento* ps, Pagina* p){
    if( ps->dados == NULL ){
        // primeira pagina
        ps->dados = p;
        return;
    }
    
    //printTitulos(ps);
    
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = p;
    e->proximo= NULL;

    Elemento* itr = ps;
    
    // inserir ordenado pelo titulo
    while( itr->proximo != NULL && myStrCmp(((Pagina*)(itr->dados))->titulo, p->titulo) < 0)
        itr = itr->proximo;
    

    e->proximo = itr->proximo;
    itr->proximo = e;

    void* dadosSwap;
    if( myStrCmp(((Pagina*)(itr->dados))->titulo, p->titulo) > 0 ){
        dadosSwap = e->dados;
        e->dados = itr->dados;
        itr->dados = dadosSwap;
    }
        
}

void paginas_destroy(Elemento** paginas){
    if( *paginas == NULL )
        return;
    
    pagina_destroy( (Pagina**) &((*paginas)->dados) );

    paginas_destroy( &((*paginas)->proximo) );
    
    free(*paginas);
}

void paginas_print(Elemento* paginas){
    Elemento* itr;
    Pagina* pActual;
    int i;
    
    // head
    printf("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\"><link rel=\"stylesheet\" type=\"text/css\" href=\"http://bootswatch.com/cosmo/bootstrap.css\"><title>Processamento de Linguagens</title></head>");
    
    // inicio do body
    printf("<body style=\"width:90%%; margin-left: auto; margin-right: auto; margin-top: 25px;\"><a name=\"top\"></a>");
    printf("<div class=\"panel panel-default\"><div class=\"panel-body\"><h2><b>N</b>ot <b>A</b>nother <b>W</b>ikipedia <b>P</b>arser<img src=\"http://corpora.di.uminho.pt/linguateca/pagina_linguateca/logoUM.jpg\" alt=\"Escola de Engenharia da Universidade do Minho\" width=\"150\" height=\"75\" align=\"top;\" style=\"float:right;position:relative;bottom:20px\"></h2></div></div><div class=\"panel panel-default\"><div class=\"panel-heading\"><h3>Índice de páginas</h3></div><div class=\"panel-body\"><dl>");
    
    // lista de paginas
    i=0;
    itr = paginas;
    while( itr ){
        pActual = (Pagina*) itr->dados;
        pActual->indice = i++;
        printf("<dt><a href=\"#pagina%d\">%s</a></dt>\n", pActual->indice, pActual->titulo);
        //pagina_print( (Pagina*)itr->dados);
        itr = itr->proximo;
    }
    printf("</dl></div></div>");
    
    // imprimir as páginas
    itr = paginas;
    while( itr ){
        pagina_print( (Pagina*)itr->dados);
        itr = itr->proximo;
    }
    printf("</dl></div></div>");
    
    
    // terminar o HTML
    printf("</body></html>\n\n");
}





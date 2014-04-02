#ifndef __PAGINA_H
#define __PAGINA_H

#include "ilink.h"
#include "elemento.h"

typedef struct sPagina {
   char* titulo;
   char* autor;
   char* ultimaRev;

   // links internos
   Elemento* iLinks;
   int nILinks;

   // links externos
   Elemento* hLinks;
   int nHLinks;
   
   // headers
   Elemento* seccoes;
   int nSeccoes;
} Pagina;


// cria uma nova página
Pagina* pagina_create();

// destroi a página
void pagina_destroy(Pagina** p);

// insere o titulo
void pagina_set_titulo(Pagina* p, char* str);

// insere o autor
void pagina_set_autor(Pagina* p, char* str);

// insere o ultimaRevisao
void pagina_set_ultimaRevisao(Pagina* p, char* str);


// imprimir o HTML da página
void pagina_print(Pagina* p);

#endif

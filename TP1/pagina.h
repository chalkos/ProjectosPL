#include "elementos.h"

typedef struct sPagina {
   char* titulo;
   char* autor;
   char* ultimaRev;

   // atalho para todos os links internos
   Elemento* iLinks;
   int nILinks;

   // atalho para todos os links externos
   Elemento* hLinks;
   int nHLinks;
   
   // atalho para todas as seccoes
   Elemento* seccoes;
   int nSeccoes;

   // todos os elementos (incluindo os referidos nos atalhos)
   Elemento* elementos;
   Elemento* actual; //atalho para obter o elemento que vai ser alterado
} Pagina;


void exemplo();

// adiciona um elemento a seguir ao elemento seleccionado
void pagina_adicionar_proximo(Pagina* p, Tipo tipo, void* dados);

// adiciona um elemento filho do elemento seleccionado
void pagina_adicionar_filho(Pagina* p, Tipo tipo, void* dados);

// mudar o actual para o elemento acima
int pagina_seleccionar_pai(Pagina* p);

// imprimir o HTML da página
void pagina_print(Pagina* p);


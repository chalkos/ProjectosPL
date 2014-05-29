#ifndef __CSV_LIB_H
#define __CSV_LIB_H

#include <stdlib.h>


/* -----------------------------------
 * Production Selectors
 * -----------------------------------
 */

#define PScons_csv_Linhas  2000
#define PScons_csv_Linhas_NIL  2001

#define PScons_csv_Linha  2002
#define PScons_csv_Linha_Fim  2003

#define PScons_csv_Campo  2004
#define PScons_csv_Campo_NIL  2005

/* -----------------------------------
 * Abstract Data Types Definition
 * -----------------------------------
 */

/* To avoid dependencies, waiting for a cleaner solution...*/

/* --- dummy Linhas ---*/
struct sLinhas;
typedef struct sLinhas *Linhas;

/* --- dummy Linha ---*/
struct sLinha;
typedef struct sLinha *Linha;

/* --- dummy Campo ---*/
struct sCampo;
typedef struct sCampo *Campo;

/* Now the types definition...*/

/* --- Linhas ---*/
struct sLinhas 
{ int flag;
  union {  
    struct {
        Linha s1;
        Linhas s2;
      } d1;
    struct {
      } d2;

  } u;
};

/* --- Linha ---*/
struct sLinha 
{ int flag;
  union {  
    struct {
        Linha s1;
        Campo s2;
      } d1;
    struct {
        Campo s1;
      } d2;

  } u;
};

/* --- Campo ---*/
struct sCampo 
{ int flag;
  union {  
    struct {
        char * s1;
      } d1;
    struct {
      } d2;

  } u;
};

/* -----------------------------------
 * Custom Datatypes definition
 * -----------------------------------
 */

typedef struct sLcsv {
    struct sLcsv *next;
    Linhas csv;
} *Lcsv;

extern Lcsv ListaCSV;

/* -----------------------------------
 * Constructor Function Signatures
 * -----------------------------------
 */

Linhas  cons_csv_Linhas( Linha a1, Linhas a2);
Linhas  cons_csv_Linhas_NIL();

Linha  cons_csv_Linha( Linha a1, Campo a2);
Linha  cons_csv_Linha_Fim( Campo a1);

Campo  cons_csv_Campo( char * a1);
Campo  cons_csv_Campo_NIL();


/* -----------------------------------
 * Custom Function Signatures
 * -----------------------------------
 */
void csv_print( Linhas csv );
Linha csv_Linha_reverse( Linha l );
int csv_Linhas_validate (Linhas lcsv);

void csv_import_csv( Linhas dados );
int csv_tempo_to_int(char* str);

// indice_campo é 1-based
char* csv_get_campo(Linha campos, int indice_campo);

/* -----------------------------------
 * Destructor Function Implementations
 * -----------------------------------
 */

void csv_free_ListaCSV(Lcsv elem);

void free_csv_Campo (Campo cmp);
void free_csv_Linha (Linha l);
void free_csv_Linhas (Linhas lcsv);

#endif

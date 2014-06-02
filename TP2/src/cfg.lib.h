#ifndef __CFG_LIB_H
#define __CFG_LIB_H

/* -----------------------------------
 * Production Selectors
 * -----------------------------------
 */

#define PScons_cfg_Confs  2000
#define PScons_cfg_Confs_NIL  2001

#define PScons_cfg_Conf_Titulo  2002
#define PScons_cfg_Conf_Nprovas  2003
#define PScons_cfg_Conf_Ntop  2004
#define PScons_cfg_Conf_Campos  2005
#define PScons_cfg_Conf_Tempo  2006
#define PScons_cfg_Conf_Chave  2007
#define PScons_cfg_Conf_Nome  2008

#define PScons_cfg_Lcampos_Lcampos  2009
#define PScons_cfg_Lcampos_Campo  2010

/* -----------------------------------
 * Abstract Data Types Definition
 * -----------------------------------
 */

/* To avoid dependencies, waiting for a cleaner solution...*/

/* --- dummy Confs ---*/
struct sConfs;
typedef struct sConfs *Confs;

/* --- dummy Conf ---*/
struct sConf;
typedef struct sConf *Conf;

/* --- dummy Lcampos ---*/
struct sLcampos;
typedef struct sLcampos *Lcampos;

/* Now the types definition...*/

/* --- Confs ---*/
struct sConfs 
{ int flag;
  union {  
    struct {
        Conf s1;
        Confs s2;
      } d1;
    struct {
      } d2;

  } u;
};

/* --- Conf ---*/
struct sConf 
{ int flag;
  union {  
    struct {
        char * s1;
      } d1;
    struct {
        int s1;
      } d2;
    struct {
        int s1;
      } d3;
    struct {
        Lcampos s1;
      } d4;
    struct {
        int s1;
      } d5;
    struct {
        int s1;
      } d6;
    struct {
        int s1;
      } d7;

  } u;
};

/* --- Lcampos ---*/
struct sLcampos 
{ int flag;
  union {  
    struct {
        Lcampos s1;
        int s2;
      } d1;
    struct {
        int s1;
      } d2;

  } u;
};

/* -----------------------------------
 * Constructor Function Signatures
 * -----------------------------------
 */

Confs  cons_cfg_Confs( Conf a1, Confs a2);
Confs  cons_cfg_Confs_NIL();

Conf  cons_cfg_Conf_Titulo( char * a1);
Conf  cons_cfg_Conf_Nprovas( int a1);
Conf  cons_cfg_Conf_Ntop( int a1);
Conf  cons_cfg_Conf_Campos( Lcampos a1);
Conf  cons_cfg_Conf_Tempo( int a1);
Conf  cons_cfg_Conf_Chave( int a1);
Conf  cons_cfg_Conf_Nome( int a1);

Lcampos  cons_cfg_Lcampos_Lcampos( Lcampos a1, int a2);
Lcampos  cons_cfg_Lcampos_Campo( int a1);

/* -----------------------------------
 * Custom Function Signatures
 * -----------------------------------
 */

void cfg_Confs_print( Confs cfgs );
int cfg_Confs_validate( Confs cfgs );
Lcampos cfg_Lcampos_reverse( Lcampos l );

// getters
int cfg_get_Nprovas( Confs cfgs );
int cfg_get_Ntop( Confs cfgs );
int cfg_get_Tempo( Confs cfgs );
int cfg_get_Chave( Confs cfgs );
int cfg_get_Nome( Confs cfgs );
char* cfg_get_Titulo( Confs cfgs );

// obtém um array de inteiros com os campos. terminado com -1
int* cfg_get_Campos( Confs cfgs );
int cfg_get_NCampos( Confs cfgs );

// obtém um array de bytes que está a 1 nos campos que foram seleccionados
char* cfg_Campos_seleccionado( Confs cfgs, int totalCampos );

/* -----------------------------------
 * Destructor Function Signatures
 * -----------------------------------
 */

void free_cfg_Lcampos( Lcampos campos );
void free_cfg_Conf( Conf cfg );
void free_cfg_Confs( Confs cfgs );

#endif

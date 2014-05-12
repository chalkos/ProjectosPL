#ifndef __CFG_LIB_H
#define __CFG_LIB_H

/* -----------------------------------
 * Custom Data Types Definition
 * -----------------------------------
 */

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
#define PScons_cfg_Conf_Score  2006

#define PScons_cfg_Lcampos_Lcampos  2007
#define PScons_cfg_Lcampos_Campo  2008

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
 * Custom Function Signatures
 * -----------------------------------
 */

void cfg_Confs_print( Confs cfgs );

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
Conf  cons_cfg_Conf_Score( int a1);

Lcampos  cons_cfg_Lcampos_Lcampos( Lcampos a1, int a2);
Lcampos  cons_cfg_Lcampos_Campo( int a1);

#endif

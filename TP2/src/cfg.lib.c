#include <stdlib.h>
#include <stdio.h>
#include "cfg.lib.h"
/* -----------------------------------
 * Custom Function Implementations
 * -----------------------------------
 */

void cfg_Confs_print( Confs cfgs ){
    Conf cfg;
    Lcampos cmps;
    while( cfgs->flag != PScons_cfg_Confs_NIL ){
        cfg = cfgs->u.d1.s1;
        switch( cfg->flag ){
            case PScons_cfg_Conf_Titulo:
                printf("Titulo: %s\n", cfg->u.d1.s1);
                break;
            case PScons_cfg_Conf_Nprovas:
                printf("Nprovas: %d\n", cfg->u.d2.s1);
                break;
            case PScons_cfg_Conf_Ntop:
                printf("Ntop: %d\n", cfg->u.d3.s1);
                break;
            case PScons_cfg_Conf_Campos:
                printf("Campos: ");
                cmps = cfg->u.d4.s1;
                while( cmps->flag == PScons_cfg_Lcampos_Lcampos ){
                    printf("#%d, ", cmps->u.d1.s2);
                    cmps = cmps->u.d1.s1;
                }
                // cmps->flag == PScons_cfg_Lcampos_Campo
                printf("#%d\n", cmps->u.d2.s1);
                break;
            case PScons_cfg_Conf_Score:
                printf("Coluna do score: #%d\n", cfg->u.d5.s1);
                break;
            default:
                printf("WARNING: flag %d no Conf ignorada!\n", cfg->flag);
        }

        cfgs = cfgs->u.d1.s2;
    }
}

/* -----------------------------------
 * Constructor Function Implementations
 * -----------------------------------
 */

Confs  cons_cfg_Confs( Conf a1, Confs a2)
{
    Confs aux0;

  aux0 = (Confs) malloc(sizeof(struct sConfs));
  aux0->flag = PScons_cfg_Confs;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

Confs  cons_cfg_Confs_NIL()
{
    Confs aux0;

  aux0 = (Confs) malloc(sizeof(struct sConfs));
  aux0->flag = PScons_cfg_Confs_NIL;
  return(aux0);
}


Conf  cons_cfg_Conf_Titulo( char * a1)
{
    Conf aux0;

  aux0 = (Conf) malloc(sizeof(struct sConf));
  aux0->flag = PScons_cfg_Conf_Titulo;
  aux0->u.d1.s1 = a1;
  return(aux0);
}

Conf  cons_cfg_Conf_Nprovas( int a1)
{
    Conf aux0;

  aux0 = (Conf) malloc(sizeof(struct sConf));
  aux0->flag = PScons_cfg_Conf_Nprovas;
  aux0->u.d2.s1 = a1;
  return(aux0);
}

Conf  cons_cfg_Conf_Ntop( int a1)
{
    Conf aux0;

  aux0 = (Conf) malloc(sizeof(struct sConf));
  aux0->flag = PScons_cfg_Conf_Ntop;
  aux0->u.d3.s1 = a1;
  return(aux0);
}

Conf  cons_cfg_Conf_Campos( Lcampos a1)
{
    Conf aux0;

  aux0 = (Conf) malloc(sizeof(struct sConf));
  aux0->flag = PScons_cfg_Conf_Campos;
  aux0->u.d4.s1 = a1;
  return(aux0);
}

Conf  cons_cfg_Conf_Score( int a1)
{
    Conf aux0;

  aux0 = (Conf) malloc(sizeof(struct sConf));
  aux0->flag = PScons_cfg_Conf_Score;
  aux0->u.d5.s1 = a1;
  return(aux0);
}


Lcampos  cons_cfg_Lcampos_Lcampos( Lcampos a1, int a2)
{
    Lcampos aux0;

  aux0 = (Lcampos) malloc(sizeof(struct sLcampos));
  aux0->flag = PScons_cfg_Lcampos_Lcampos;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

Lcampos  cons_cfg_Lcampos_Campo( int a1)
{
    Lcampos aux0;

  aux0 = (Lcampos) malloc(sizeof(struct sLcampos));
  aux0->flag = PScons_cfg_Lcampos_Campo;
  aux0->u.d2.s1 = a1;
  return(aux0);
}



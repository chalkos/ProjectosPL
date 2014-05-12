#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cfg.lib.h"
/* -----------------------------------
 * Custom Function Implementations
 * -----------------------------------
 */
int cfg_Confs_validate( Confs cfgs ){
    int n_titulos = 0;
    int n_nprovas = 0;
    int n_ntop    = 0;
    int n_campos  = 0; // numero de tags =campos=
    int n_score   = 0;
    
    Conf cfg;
    while( cfgs->flag != PScons_cfg_Confs_NIL ){
        cfg = cfgs->u.d1.s1;
        switch( cfg->flag ){
            case PScons_cfg_Conf_Titulo:
                n_titulos++;
                break;
            case PScons_cfg_Conf_Nprovas:
                n_nprovas++;
                break;
            case PScons_cfg_Conf_Ntop:
                n_ntop++;
                break;
            case PScons_cfg_Conf_Campos:
                n_campos++;
                break;
            case PScons_cfg_Conf_Score:
                n_score++;
                break;
            default:
                fprintf(stderr, "WARNING: flag %d na struct Conf ignorada!\n", cfg->flag);
        }

        cfgs = cfgs->u.d1.s2;
    }

    if( n_titulos > 1 )
        fprintf(stderr, "WARNING: Encontrados %d =titulo=\n", n_titulos);
    if( n_nprovas > 1 )
        fprintf(stderr, "WARNING: Encontrados %d =nprovas=\n", n_nprovas);
    if( n_ntop > 1 )
        fprintf(stderr, "WARNING: Encontrados %d =ntop=\n", n_ntop);
    if( n_score > 1 )
        fprintf(stderr, "WARNING: Encontrados %d =score=.\n", n_score);
    if( n_campos > 1 )
        fprintf(stderr, "WARNING: Encontrados %d =campos=.\n", n_campos);
    //TODO: ver como lidar de forma genérica com erros e warnings, tanto nos módulos como no yacc.

    return 1; //tudo bem
}

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
        }

        cfgs = cfgs->u.d1.s2;
    }
}

Lcampos cfg_Lcampos_reverse( Lcampos l ){
    int val;
    Lcampos root = l;
    Lcampos r;

    if( l->flag == PScons_cfg_Lcampos_Campo )
        return l;
    
    val = l->u.d1.s2;
    l = l->u.d1.s1;
    r = cons_cfg_Lcampos_Campo(val);
        
    while( l->flag == PScons_cfg_Lcampos_Lcampos ){
        val = l->u.d1.s2;
        l = l->u.d1.s1;
        r = cons_cfg_Lcampos_Lcampos(r, val);
    }
    
    r = cons_cfg_Lcampos_Lcampos(r, l->u.d2.s1);
    
    free_cfg_Lcampos( root );
    
    return r;
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

/* -----------------------------------
 * Destructor Function Implementations
 * -----------------------------------
 */

void free_cfg_Lcampos( Lcampos campos ){
    if( campos->flag == PScons_cfg_Lcampos_Lcampos )
        free_cfg_Lcampos( campos->u.d1.s1 );

    free( campos );
}

void free_cfg_Conf( Conf cfg ){
    switch( cfg->flag ){
        case PScons_cfg_Conf_Titulo:
            free( cfg->u.d1.s1 );
            break;
        case PScons_cfg_Conf_Campos:
            free_cfg_Lcampos( cfg->u.d4.s1 );
            break;
    }
    
    free( cfg );
}

void free_cfg_Confs( Confs cfgs ){
    if( cfgs->flag == PScons_cfg_Confs ){
        free_cfg_Conf( cfgs->u.d1.s1 );
        free_cfg_Confs( cfgs->u.d1.s2 );
    }
    free( cfgs );
}

#ifndef _MOD_ARV_H
#define _MOD_ARV_H

#include <stdio.h>
#include <stdlib.h>
#include "arv.lib.h"
/* -----------------------------------
 * Constructor Function Implementations
 * -----------------------------------
 */

Arv  cons_arv( int a1, Arv a2, Arv a3)
{
    Arv aux0;

  aux0 = (Arv) malloc(sizeof(struct sArv));
  aux0->flag = PScons_arv;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  aux0->u.d1.s3 = a3;
  return(aux0);
}

Arv  cons_arv_NIL()
{
    Arv aux0;

  aux0 = (Arv) malloc(sizeof(struct sArv));
  aux0->flag = PScons_arv_NIL;
  return(aux0);
}

// mais funções


int arv_verifica( Arv a ){
    // ta mal, era preciso ver que o valor do nodo
    // era maior que o maior valor à sua esquerda
    // e que o valor do nodo era menor que o menor
    // valor à sua direita.
    // seria preciso criar mais duas funções (max e min).
    if( a->flag == PScons_arv_NIL )
        return 1;

    if( a->u.d1.s2->flag == PScons_arv ){
        if( a->u.d1.s2->u.d1.s1 < a->u.d1.s1 ){
            if( !arv_verifica( a->u.d1.s2 ) )
                return 0;
        }
    }
    
    if( a->u.d1.s3->flag == PScons_arv ){
        if( a->u.d1.s3->u.d1.s1 > a->u.d1.s1 ){
            if( !arv_verifica( a->u.d1.s3 ) )
                return 0;
        }
    }

    return 1;
}

void arv_inorder( Arv a ){
    if( a->flag == PScons_arv_NIL )
        return;

    arv_inorder( a->u.d1.s3 );
    printf("%d ", a->u.d1.s1);
    arv_inorder( a->u.d1.s2 );
}
int arv_soma( Arv a ){
    if( a->flag == PScons_arv_NIL )
        return 0;

    return a->u.d1.s1 +
           arv_conta( a->u.d1.s2 ) +
           arv_conta( a->u.d1.s3 );
}
int arv_conta( Arv a ){
    if( a->flag == PScons_arv_NIL )
        return 0;

    return 1 +
           arv_conta( a->u.d1.s2 ) +
           arv_conta( a->u.d1.s3 );
}

#endif

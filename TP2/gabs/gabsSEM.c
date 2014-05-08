/* ----------------------------------------------
 * gabsSEM.c
 *
 * Semantic Functions: implementation file
 * ----------------------------------------------
 */

#include <stdio.h>
#include "gabsGA.h"
#include "gabsSEM.h"


void showBlockList( BlockList bl )
{
  if(bl->flag != BLOCKLISTNIL)
    {
      showBlock(bl->u.blocklist.b);
      showBlockList(bl->u.blocklist.bl);
    }
}


void showBlock( Block b )
{
  printf("  %s : ", b->u.block.simbN);
  showDList(b->u.block.dl);
  printf("  ;\n\n");
}


void showDList( DList dl )
{
  if(dl->flag == DLISTNIL)
    printf("\n");
  else
    {
      showDeriv(dl->u.dlist.d);
      if(dl->u.dlist.dl->flag != DLISTNIL)
        printf("\n  | ");
      showDList(dl->u.dlist.dl);
    }
}


void showDeriv( Deriv d )
{
  showSimbList(d->u.deriv.sl);
}


void showSimbList( SimbList sl )
{
  if(sl->flag != SIMBLISTNIL)
    { showSimb(sl->u.simblist.s);
      printf(" ");
      showSimbList(sl->u.simblist.sl);
    }
}


void showSimb( Simb s )
{
  if(s->flag == TERMINAL)
    printf("%s",s->u.term.s);
  else
    printf("%s",s->u.nterm.s);
}

    

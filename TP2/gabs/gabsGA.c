/* --------------------------------------------------
 * Abstract Grammar for abstract grammars
 * gabsGA.c - Implementation file
 */

#include <stdlib.h>
#include "gabsGA.h"

Simb cons_Term(char *s)
{
  Simb aux;
  
  aux = (Simb)malloc(sizeof(struct sSimb));
  aux->flag = TERMINAL;
  aux->u.term.s = s;

  return aux;
}


Simb cons_NTerm(char *s)
{
  Simb aux;
  
  aux = (Simb)malloc(sizeof(struct sSimb));
  aux->flag = NTERMINAL;
  aux->u.nterm.s = s;

  return aux;
}



SimbList cons_SimbList(Simb s, SimbList sl)
{
  SimbList aux;
  
  aux = (SimbList)malloc(sizeof(struct sSimbList));
  aux->flag = SIMBLIST;
  aux->u.simblist.s = s;
  aux->u.simblist.sl = sl;

  return aux;
}


SimbList cons_SimbListNil()
{
  SimbList aux;
  
  aux = (SimbList)malloc(sizeof(struct sSimbList));
  aux->flag = SIMBLISTNIL;

  return aux;
}


Deriv cons_Deriv(char *s, SimbList sl)
{
  Deriv aux;
  
  aux = (Deriv)malloc(sizeof(struct sDeriv));
  aux->flag = DERIV;
  aux->u.deriv.id = s;
  aux->u.deriv.sl = sl;

  return aux;
}



DList cons_DList(Deriv d, DList dl)
{
  DList aux;
  
  aux = (DList)malloc(sizeof(struct sDList));
  aux->flag = DLIST;
  aux->u.dlist.d = d;
  aux->u.dlist.dl = dl;

  return aux;
}


DList cons_DListNil()
{
  DList aux;
  
  aux = (DList)malloc(sizeof(struct sDList));
  aux->flag = DLISTNIL;

  return aux;
}



Block cons_Block(char *s, DList dl)
{
  Block aux;
  
  aux = (Block)malloc(sizeof(struct sBlock));
  aux->flag = BLOCK;
  aux->u.block.simbN = s;
  aux->u.block.dl = dl;

  return aux;
}



BlockList cons_BlockList(Block b, BlockList bl)
{
  BlockList aux;
  
  aux = (BlockList)malloc(sizeof(struct sBlockList));
  aux->flag = BLOCKLIST;
  aux->u.blocklist.b = b;
  aux->u.blocklist.bl = bl;

  return aux;
}


BlockList cons_BlockListNil()
{
  BlockList aux;
  
  aux = (BlockList)malloc(sizeof(struct sBlockList));
  aux->flag = BLOCKLISTNIL;

  return aux;
}




/* ----------------------------------------------
 * gabsCODE.c
 *
 * C Code generation: implementation file
 * ----------------------------------------------
 */

#include <stdio.h>
#include "gabsGA.h"
#include "gabsCODE.h"

/* ----------------------------------------------
 * Main driver function for code generation
 * ----------------------------------------------
 */

void codeGeneration( BlockList bl )
{
      printf("/* -----------------------------------\n");
      printf(" * Production Selectors\n");
      printf(" * -----------------------------------\n");
      printf(" */\n\n");
  psBlockList(bl);
      printf("/* -----------------------------------\n");
      printf(" * Abstract Data Types Definition\n");
      printf(" * -----------------------------------\n");
      printf(" */\n\n");
      printf("/* To avoid dependencies, waiting for a cleaner solution...*/\n\n");
  codeBlockListAUX(bl);
      printf("/* Now the types definition...*/\n\n");
  codeBlockList(bl);
      printf("/* -----------------------------------\n");
      printf(" * Constructor Function Signatures\n");
      printf(" * -----------------------------------\n");
      printf(" */\n\n");
  cfBlockList(bl);
      printf("/* -----------------------------------\n");
      printf(" * Constructor Function Implementations\n");
      printf(" * -----------------------------------\n");
      printf(" */\n\n");
  cfiBlockList(bl);
}


/* ----------------------------------------------
 * AST traversal to free dependencies in type definition
 * ----------------------------------------------
 */

void codeBlockListAUX( BlockList bl )
{
  if(bl->flag != BLOCKLISTNIL)
    {
      codeBlockAUX(bl->u.blocklist.b);
      codeBlockListAUX(bl->u.blocklist.bl);
    }
}


void codeBlockAUX( Block b )
{
  printf("/* --- dummy %s ---*/\n", b->u.block.simbN);
  printf("struct s%s;\n", b->u.block.simbN);
  printf("typedef struct s%s *%s;\n\n", b->u.block.simbN, b->u.block.simbN);
}


/* ----------------------------------------------
 * AST traversal for the abstract data types generation
 * ----------------------------------------------
 */

void codeBlockList( BlockList bl )
{
  if(bl->flag != BLOCKLISTNIL)
    {
      codeBlock(bl->u.blocklist.b);
      codeBlockList(bl->u.blocklist.bl);
    }
}


void codeBlock( Block b )
{
  printf("/* --- %s ---*/\n", b->u.block.simbN);
  printf("struct s%s \n", b->u.block.simbN);
  printf("{ int flag;\n  union {  \n");
  codeDList(b->u.block.dl,1);
  printf("  } u;\n};\n\n", b->u.block.simbN);
}


void codeDList( DList dl, int dcont)
{
  if(dl->flag == DLISTNIL)
    printf("\n");
  else
    {
      printf("    struct {\n");
      codeDeriv(dl->u.dlist.d);
      printf("      } d%d;\n",dcont);
      codeDList(dl->u.dlist.dl,++dcont);
    }
}


void codeDeriv( Deriv d )
{
  codeSimbList(d->u.deriv.sl, 1);
}


void codeSimbList( SimbList sl, int scont )
{
  if(sl->flag != SIMBLISTNIL)
    { codeSimb(sl->u.simblist.s, scont);
      codeSimbList(sl->u.simblist.sl, ++scont);
    }
}


void codeSimb( Simb s, int scont )
{
  if(s->flag == TERMINAL)
    printf("        %s s%d;\n",s->u.term.s, scont);
  else
    printf("        %s s%d;\n",s->u.nterm.s, scont);
}

    
/* ----------------------------------------------
 * AST traversal for production selectors generation
 * ----------------------------------------------
 */

int production = 0;

void psBlockList( BlockList bl )
{
  if(bl->flag != BLOCKLISTNIL)
    {
      psBlock(bl->u.blocklist.b);
      psBlockList(bl->u.blocklist.bl);
    }
}


void psBlock( Block b )
{
  psDList(b->u.block.dl);
}


void psDList( DList dl)
{
  if(dl->flag == DLISTNIL)
    printf("\n");
  else
    {
      psDeriv(dl->u.dlist.d);
      psDList(dl->u.dlist.dl);
    }
}


void psDeriv( Deriv d )
{
  printf("#define PS%s  %d\n", d->u.deriv.id, 2000+(production++));
}



/* ----------------------------------------------
 * AST traversal for constructor function signature generation
 * ----------------------------------------------
 */

void cfBlockList( BlockList bl )
{
  if(bl->flag != BLOCKLISTNIL)
    {
      cfBlock(bl->u.blocklist.b);
      cfBlockList(bl->u.blocklist.bl);
    }
}


void cfBlock( Block b )
{
  cfDList(b->u.block.dl, b->u.block.simbN);
}


void cfDList( DList dl, char *cftype)
{
  if(dl->flag == DLISTNIL)
    printf("\n");
  else
    {
      printf("%s ", cftype);
      cfDeriv(dl->u.dlist.d);
      cfDList(dl->u.dlist.dl, cftype);
    }
}


void cfDeriv( Deriv d )
{
  printf(" %s(", d->u.deriv.id);
  cfSimbList( d->u.deriv.sl, 1 );
  printf(");\n");
}


void cfSimbList( SimbList sl, int scont )
{
  if(sl->flag != SIMBLISTNIL)
    { cfSimb(sl->u.simblist.s, scont);
      if(sl->u.simblist.sl->flag != SIMBLISTNIL)
        printf(",");
      cfSimbList(sl->u.simblist.sl, ++scont);
    }
}


void cfSimb( Simb s, int scont )
{
  if(s->flag == TERMINAL)
    printf(" %s a%d",s->u.term.s, scont);
  else
    printf(" %s a%d",s->u.nterm.s, scont);
}



/* ----------------------------------------------
 * AST traversal for constructor function mplementation generation: .c
 * ----------------------------------------------
 */

void cfiBlockList( BlockList bl )
{
  if(bl->flag != BLOCKLISTNIL)
    {
      cfiBlock(bl->u.blocklist.b);
      cfiBlockList(bl->u.blocklist.bl);
    }
}


void cfiBlock( Block b )
{
  cfiDList(b->u.block.dl, b->u.block.simbN, 1);
}


void cfiDList( DList dl, char *cftype, int dcont)
{
  if(dl->flag == DLISTNIL)
    printf("\n");
  else
    {
      printf("%s ", cftype);
      cfiDeriv(dl->u.dlist.d, cftype, dcont);
      cfiDList(dl->u.dlist.dl, cftype, ++dcont);
    }
}


void cfiDeriv( Deriv d, char *cftype, int dcont )
{
  printf(" %s(", d->u.deriv.id);
  cfSimbList( d->u.deriv.sl, 1 );
  printf(")\n{\n  ");
  printf("  %s aux0;\n\n", cftype);
  printf("  aux0 = (%s) malloc(sizeof(struct s%s));\n", cftype, cftype);
  printf("  aux0->flag = PS%s;\n", d->u.deriv.id);
  cfiSimbList( d->u.deriv.sl, 1, dcont );
  printf("  return(aux0);\n");
  printf("}\n\n");
}


void cfiSimbList( SimbList sl, int scont, int dcont )
{
  if(sl->flag != SIMBLISTNIL)
    { cfiSimb(sl->u.simblist.s, scont, dcont);
      cfiSimbList(sl->u.simblist.sl, ++scont, dcont);
    }
}


void cfiSimb( Simb s, int scont, int dcont )
{
  printf("  aux0->u.d%d.s%d = a%d;\n", dcont, scont, scont);
}


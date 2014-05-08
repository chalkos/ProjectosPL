
/*
 * listas.c
 * Recursive descencent Parser for Abstract Grammars
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "gabsGA.h"
#include "gabsSEM.h"
#include "gabsCODE.h"

extern int yylex();

static int prox_simb;

int da_simbolo()
{ return yylex(); }

char* rec_term(int simb)
{ char *aux;

  if(prox_simb == simb)
  {
	aux = yylval;
	prox_simb = da_simbolo();
	return aux;
  }
  else{
	fprintf(stderr, "ERROR: unexpexpected token = %d",prox_simb);
	exit(1);
  }
}


void error()
{ fprintf(stderr, "ERROR: Syntactic, near - %d", prox_simb);
  exit(2);
}


/* ----
   Parser functions declaration
   ----
*/
BlockList rec_Gabs();
BlockList rec_BlockList();
Block rec_Block();
DList rec_DList();
DList rec_DList2();
Deriv rec_Deriv();
SimbList rec_SimbList();
Simb rec_Simb();

/* ------------------------------------------- */
/* ----
   TOKENIZER - debug only
   -----
*/

void tokenizer()
{
while(prox_simb)
  {
	printf("%d\n",prox_simb);
	prox_simb=da_simbolo();
  }
  exit(0);
}


/* ------------------------------------------- */
/* ----
   THE PARSER
   -----
*/

main()
{ BlockList res;

  prox_simb = da_simbolo();
  res = rec_Gabs();
  // showBlockList(res);
  codeGeneration(res);
  // tokenizer();
}


BlockList rec_Gabs()
{ BlockList aux;

  rec_term(OGA);
  aux = rec_BlockList();
  rec_term(CGA);

  return aux;
}


BlockList rec_BlockList()
{ BlockList aux;
  Block baux;

  switch(prox_simb)
  {
	case CGA: aux = cons_BlockListNil();
					break;
	case SIMBN: baux = rec_Block();
				rec_term(SEP);
				aux = cons_BlockList( baux, rec_BlockList());
				break;
	default: error();
  }
  return aux;
}


Block rec_Block()
{ char *saux;

  saux = rec_term(SIMBN);
  rec_term(ODLIST);
  return cons_Block( saux, rec_DList() );
}


DList rec_DList()
{
  Deriv daux;

  daux = rec_Deriv();
  return cons_DList( daux, rec_DList2() );
}


DList rec_DList2()
{ DList aux;
  Deriv daux;

  switch(prox_simb)
  { case CGA:
	case SEP: aux = cons_DListNil();
			  break;
	case SEPDLIST: rec_term(SEPDLIST);
				   daux = rec_Deriv();
				   aux = cons_DList( daux, rec_DList2() );
				   break;
	default: error();
  }
  return aux;
}


Deriv rec_Deriv()
{ SimbList aux;
  char *saux;

  saux = rec_term(ID);
  rec_term(ODER);
  aux = rec_SimbList();
  rec_term(CDER);

  return cons_Deriv( saux, aux );
}


SimbList rec_SimbList()
{ SimbList aux;
  Simb saux;

  switch(prox_simb)
  { case CDER: aux = cons_SimbListNil();
			   break;
	case SIMBN:
	case SIMBT: saux = rec_Simb();
				aux = cons_SimbList( saux, rec_SimbList() );
				break;
	default: error();
  }
  return aux;
}


Simb rec_Simb()
{ Simb aux;

  switch(prox_simb)
  { case SIMBN: aux = cons_Term(rec_term(SIMBN));
				break;
	case SIMBT: aux = cons_NTerm(rec_term(SIMBT));
				break;
	default: error();
  }
  return aux;
}

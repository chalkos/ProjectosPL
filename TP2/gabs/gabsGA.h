/* --------------------------------------------------
 * Abstract Grammar for abstract grammars
 */

#ifndef _GabsGA
#define _GabsGA

typedef struct sSimb
{
  int flag;
  union {
    struct {
      char * s;
      } term;
    struct {
      char * s;
      } nterm;
  } u;
} *Simb;

#define TERMINAL 2001
#define NTERMINAL 2002

Simb cons_Term(char *s);
Simb cons_NTerm(char *s);


typedef struct sSimbList
{
  int flag;
  union {
    struct {
      Simb s;
      struct sSimbList *sl;
      } simblist;
    struct {
      } simblistnil;
  } u;
} *SimbList;

#define SIMBLISTNIL 2003
#define SIMBLIST 2004

SimbList cons_SimbList(Simb s, SimbList sl);
SimbList cons_SimbListNil();


typedef struct sDeriv
{
  int flag;
  union {
    struct {
      char * id;
      SimbList sl;
      } deriv;
  } u;
} *Deriv;

#define DERIV 2005

Deriv cons_Deriv(char *s, SimbList sl);


typedef struct sDList
{
  int flag;
  union {
    struct {
      Deriv d;
      struct sDList *dl;
      } dlist;
    struct {
      } dlistnil;
  } u;
} *DList;

#define DLIST 2008
#define DLISTNIL 2006

DList cons_DList(Deriv d, DList dl);
DList cons_DListNil();


typedef struct sBlock
{
  int flag;
  union {
    struct {
      char * simbN;
      DList dl;
      } block;
  } u;
} *Block;

#define BLOCK 2009

Block cons_Block(char *s, DList dl);


typedef struct sBlockList
{
  int flag;
  union {
    struct {
      } blocklistnil;
    struct {
      Block b;
      struct sBlockList *bl;
      } blocklist;
  } u;
} *BlockList;

#define BLOCKLIST 2010
#define BLOCKLISTNIL 2011

BlockList cons_BlockList(Block b, BlockList bl);
BlockList cons_BlockListNil();

#endif

/* -----------------------------------
 * Production Selectors
 * -----------------------------------
 */

#define PScons_arv  2000
#define PScons_arv_NIL  2001

/* -----------------------------------
 * Abstract Data Types Definition
 * -----------------------------------
 */

/* To avoid dependencies, waiting for a cleaner solution...*/

/* --- dummy Arv ---*/
struct sArv;
typedef struct sArv *Arv;

/* Now the types definition...*/

/* --- Arv ---*/
struct sArv 
{ int flag;
  union {  
    struct {
        int s1;
        Arv s2;
        Arv s3;
      } d1;
    struct {
      } d2;

  } u;
};

/* -----------------------------------
 * Constructor Function Signatures
 * -----------------------------------
 */

Arv  cons_arv( int a1, Arv a2, Arv a3);
Arv  cons_arv_NIL();

// mais funções
//
//

int arv_verifica( Arv a );
void arv_inorder( Arv a );
int arv_soma( Arv a );
int arv_conta( Arv a );


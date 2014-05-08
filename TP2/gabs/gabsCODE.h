
/* ----------------------------------------------
 * gabsCODE.h
 *
 * C Code Generation : header file
 * ----------------------------------------------
 */

void codeBlockList( BlockList bl );
void codeBlock( Block b );
void codeDList( DList dl, int dcont );
void codeDeriv( Deriv d );
void codeSimbList( SimbList sl, int scont );
void codeSimb( Simb s, int scont );

    
void psBlockList( BlockList bl );
void psBlock( Block b );
void psDList( DList dl );
void psDeriv( Deriv d );


void cfBlockList( BlockList bl );
void cfBlock( Block b );
void cfDList( DList dl, char *cftype );
void cfDeriv( Deriv d );
void cfSimbList( SimbList sl, int scont );
void cfSimb( Simb s, int scont );


void cfiBlockList( BlockList bl );
void cfiBlock( Block b );
void cfiDList( DList dl, char *cftype, int dcont );
void cfiDeriv( Deriv d, char *cftype, int dcont );
void cfiSimbList( SimbList sl, int scont, int dcont );
void cfiSimb( Simb s, int scont, int dcont );


void codeBlockListAUX( BlockList bl );
void codeBlockAUX( Block b );


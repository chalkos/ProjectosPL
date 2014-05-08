/* --------------------------------------------------------
 * tokens.h

 * TOKEN Declarations for Abstract Grammars 
 * -------------------------------------------------------- */

#ifndef _TOKENS
#define _TOKENS

#define OGA      1001
#define CGA      1002
#define SEP      1003
#define SEPDLIST 1004
#define ODLIST   1008
#define ID       1005
#define SIMBN    1006
#define SIMBT    1007
#define ODER     1009
#define CDER     1010

#define ERRO     -1

extern int yylineno;

/* ------
 * Estrutura de comunicaçao entre o lex e o parser
 * -----
 */

typedef char *Value;
Value yylval;

#endif

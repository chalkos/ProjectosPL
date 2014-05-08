
%{

#define TOK_IINDICE 1000
#define TOK_FINDICE 1001
#define TOK_SEPL 1002
#define TOK_SEP 1003
#define TOK_STRING 1004
#define TOK_IGUAL 1005

%}

%%

"FIM DO INDICE" return TOK_FINDICE;
INDICE          return TOK_IINDICE;
\n              return TOK_SEPL;
\,              return TOK_SEP;
\=              return TOK_IGUAL;
[A-Za-z0-9]+    return TOK_STRING;


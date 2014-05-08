%{
#include "y.tab.h"
%}

%x intag

%%
  BEGIN 0;

"<agenda>" return IAGENDA;
"</agenda>" return FAGENDA;

"<entrada" { BEGIN intag; return IENTRADA; }
"</entrada>" return FENTRADA;

"<grupo" { BEGIN intag; return IGRUPO; }
"</grupo>" return FGRUPO;

"<ref" { BEGIN intag; return IREF; }

"<nome>"      return INOME;
"</nome>"     return FNOME;
"<email>"     return IEMAIL;
"</email>"    return FEMAIL;
"<telefone>"  return ITELEFONE;
"</telefone>" return FTELEFONE;

[0-9 \-]+     return numero;
[^\n\<][^\<]*        return texto;


<intag>\>   { BEGIN 0; return '>'; }
<intag>"/>" { BEGIN 0; return FREF; }
<intag>\= return '=';
<intag>[a-zA-Z][a-zA-Z0-9\-_]* return chave;
<intag>\"[^\n\"]\" return valor;

<*>[ \n\t] ;

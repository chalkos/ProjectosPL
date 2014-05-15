%{
#define YY_NO_INPUT
#include <string.h>
#include "csv.lib.h"
#include "csv.tab.h"
%}
%option nounput

%%
[^\n\;]+ {csvlval.csv_str = strdup(csvtext);
         return str;}
\n+     {return '\n';}
\;      {return ';';}
<<EOF>> {return '$';}


%%
int csvwrap(){
	return 1;
}

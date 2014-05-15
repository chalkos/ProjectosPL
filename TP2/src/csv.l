%{
#include <string.h>
#include "csv.lib.h"
#include "csv.tab.h"
%}

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
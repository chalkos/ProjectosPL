%{
// NAO FUNCIONA, PORQUE?
char* tag;
%}

%x texto
%%

<texto>^[^\-][^\n]*    printf("%s", yytext);
<texto>\n      { BEGIN 0; printf("</%s>\n", tag); free(tag);}
<texto><<EOF>> { BEGIN 0; printf("</%s>\n", tag); free(tag); return 0;}

^\-[^\n]+  { tag=strdup(yytext+1); printf("<%s>", tag); BEGIN texto; }

. ;

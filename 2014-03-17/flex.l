%x refrao
%{
    /*
        
    */
%}
%%




{soc}\n    BEGIN refrao;
title:.*\n {yytext[ strlen(yytext)-1 ] = '\0';
            printf("<h1>%s</h1>\n", yytext+6);}
singer:.*\n {yytext[ strlen(yytext)-1 ] = '\0';
            printf("<h2>%s</h2>\n", yytext+7);}
music:.*\n {yytext[ strlen(yytext)-1 ] = '\0';
            printf("<h2>%s</h2>\n", yytext+6);}
lyrics:.*\n {yytext[ strlen(yytext)-1 ] = '\0';
            printf("<h2>%s</h2>\n", yytext+7);}
from:.*\n {yytext[ strlen(yytext)-1 ] = '\0';
            printf("<h3>%s</h3>\n", yytext+5);}
\n printf("<br/>");




%%

int prefrao(){
    
}

int yywrap(){
    printf("done!\n");
}

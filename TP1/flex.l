%x page
%x title
%x revision
%x timestamp
%x contributor
%x username
%x text
%{

%}
%%
\<page\> {printf("inicio nova pagina\n"); BEGIN page;}

<page>\<\/page\> {printf("fim pagina\n"); BEGIN 0;}
<page>\<title\> {printf("titulo: "); BEGIN title;}
<page>\<revision\> {printf("last revision: "); BEGIN revision;}

<title>\<\/title\> {printf("\n"); BEGIN page;}
<title>. {printf("%s", yytext);}

<revision>\<timestamp\> {printf("at "); BEGIN timestamp;}
<revision>\<contributor\> {printf(", by "); BEGIN contributor;}
<revision>\<\/revision\> {BEGIN page;}
<revision>\<text.*?> {printf("YEY, TEEEEXTOOOO!!!"); BEGIN text;}

<timestamp>\<\/timestamp\> {BEGIN revision;}
<timestamp>. {printf("%s", yytext);}

<contributor>\<username\> {BEGIN username;}
<contributor>\<\/contributor\> {BEGIN revision;}

<username>\<\/username\> {printf("\n"); BEGIN contributor;}
<username>. {printf("%s", yytext);}

<text>\<\/text\> {printf("\n"); BEGIN revision;}
<text>\[\[[^\]]*?\]\] {printf("LINK: %s\n", yytext);}

<*>. ;
<*>\n ;
%%
int yywrap(){
    printf("DONE!\n");
}

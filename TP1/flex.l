%x page
%x title
%x revision
%x timestamp
%x contributor
%x username
%x text

%x link_file
%x link_URL
%{
#include "hlink.h"

%}
%%
"<page>" {printf("inicio nova pagina\n"); BEGIN page;}

<page>"</page>" {printf("fim pagina\n");
                BEGIN 0;}
<page>"<title>" {printf("titulo: ");
                BEGIN title;}
<page>"<revision>" {printf("last revision: ");
                BEGIN revision;}

<title>"</title>" {printf("\n");
                BEGIN page;}
<title>. {printf("%s", yytext);}

<revision>"<timestamp>" {printf("at "); BEGIN timestamp;}
<revision>"<contributor>" {printf(", by "); BEGIN contributor;}
<revision>"</revision>" {BEGIN page;}
<revision>\<text.*?\> {/*printf("YEY, TEEEEXTOOOO!!!\n");*/ BEGIN text;}

<timestamp>"</timestamp>" {BEGIN revision;}
<timestamp>. {printf("%s", yytext);}

<contributor>"<username>" {BEGIN username;}
<contributor>"</contributor>" {BEGIN revision;}

<username>"</username>" {printf("\n"); BEGIN contributor;}
<username>. {printf("%s", yytext);}

<text>"</text>" {printf("\n"); BEGIN revision;}
<text>"[[File:" {BEGIN link_file;}
<text>"[[" {BEGIN link_URL;}

<link_file>"]]" {printf("\n"); BEGIN text;}
<link_file>. {printf("%s", yytext);}

<link_URL>Category: {hlink_set_special("Category");}
<link_URL>[^\n\[\]]+\| {hlink_set_view(
<link_URL>[^\n\[]+\]\] {if hlink.
<link_URL>\|\ *\]\] {hlink_got_rename(yytext);}
<link_URL>[^\[\n]*\]\][a-zA-Z]* {hlink_got_ending(yytext); BEGIN text;}

<*>. ;
<*>\n ;
%%
int yywrap(){
    hlink_free_all();
    printf("DONE!\n");
    return 1;
}

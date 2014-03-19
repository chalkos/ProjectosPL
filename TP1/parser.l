%x page
%x title
%x revision
%x timestamp
%x contributor
%x username
%x text

%x link_file
%x hlink1
%x hlink2
%x hlink3
%{
#include "hlink.h"

int anterior = 0;

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
<text>"[[Image:" {BEGIN link_file;}
<text,link_file>"[[":? {anterior = text; BEGIN hlink1;}

<link_file>"]]" {printf("\n"); BEGIN text;}
<link_file>. {printf("%s", yytext);}

<hlink1>[a-zA-Z]+:[^\]\(,\|]+ {printf("ABJC: %s * ",yytext); BEGIN hlink2;}
<hlink1>[^\]\(,\|]+ {printf("ABC: %s * ",yytext); BEGIN hlink2;}

<hlink2,hlink3>\]\][a-zA-Z]* {printf("DL: %s * \n\n",yytext); BEGIN anterior;}
<hlink2>\| {printf("H: %s * ",yytext); BEGIN hlink3;}
<hlink2>\([^\]\)\|]+\)\]\][a-zA-Z]* {printf("EFGDL: %s * \n\n",yytext); BEGIN anterior;}
<hlink2>\([^\]\)\|]+\)\| {printf("EFGH: %s * ",yytext); BEGIN hlink3;}
<hlink2>\([^\]\)\|]+\]\][a-zA-Z]* {printf("EFDL: %s * \n\n",yytext); BEGIN anterior;}
<hlink2>,\]\][a-zA-Z]* {printf("KDL: %s * \n\n",yytext); BEGIN anterior;}
<hlink2>,\| {printf("KH: %s * ",yytext); BEGIN hlink3;}

<hlink3>[^\]]+\]\][a-zA-Z]* {printf("IDL: %s * \n\n",yytext); BEGIN anterior;}

<hlink1,hlink2,hlink3>. ECHO;

<*>. ;
<*>\n ;
%%
int yywrap(){
    hlink_free_all();
    printf("DONE!\n");
    return 1;
}

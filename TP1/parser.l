%x page
%x title
%x revision
%x timestamp
%x contributor
%x username
%x text

%x link_file
%x ilink1
%x ilink2
%x ilink3
%x ilink4
%{
#include "pagina.h"
#include "ilink.h"

int anterior = 0;
ILink* ilink = NULL;
Pagina* pag = NULL;

%}
%%
"<page>"           {pag = pagina_create();
                    printf("inicio nova pagina\n");
                    BEGIN page;
                    }

<page>"</page>"    {printf("fim pagina\n");
                    BEGIN 0;
                    }
<page>"<title>"    {printf("titulo: ");
                    BEGIN title;
                    }
<page>"<revision>" {printf("last revision: ");
                    BEGIN revision;
                    }

<title>"</title>"  {printf("\n");
                    BEGIN page;
                    }
<title>[^<]*       { pagina_set_titulo(p,yytext); }

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
<text,link_file>"[[":? {anterior = text; BEGIN ilink1;}

<link_file>"]]" {printf("\n"); BEGIN text;}
<link_file>. {printf("%s", yytext);}

<ilink1>[a-zA-Z]+:[^\]\(,\|]+       {/*ABCJ */
                                     ilink = ilink_create();
                                     ilink_set_especial(ilink, yytext);
                                     BEGIN ilink2;
                                     }

<ilink1>[^\]\(,\|]+                 {/*ABC  */
                                     ilink = ilink_create();
                                     ilink_set_texto(ilink, yytext);
                                     BEGIN ilink2;
                                     }

<ilink2,ilink3>\]                   {/*D    */
                                     BEGIN ilink4;
                                     }

<ilink2>\|                          {/*H    */
                                     BEGIN ilink3;
                                     }

<ilink2>\([^\]\)\|]+\)\]            {/*EFGD */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     ilink_set_parenteses(ilink, yytext);
                                     BEGIN ilink4;
                                     }

<ilink2>\([^\]\)\|]+\)\|            {/*EFGH */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     ilink_set_parenteses(ilink, yytext);
                                     BEGIN ilink3;
                                     }

<ilink2>\([^\]\)\|]+\]              {/*EFD  */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     ilink_set_parenteses(ilink, yytext);
                                     BEGIN ilink4;
                                     }

<ilink2>,[^\]\|]*\]                 {/*KMD  */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     ilink_set_virgula(ilink, yytext);
                                     BEGIN ilink4;
                                     }

<ilink2>,[^\]\|]*\|                 {/*KMH  */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     ilink_set_virgula(ilink, yytext);
                                     BEGIN ilink3;
                                     }

<ilink3>[^\]]*\]                    {/*ID   */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     ilink_set_apresentar(ilink, yytext);
                                     BEGIN ilink4;
                                     }

<ilink4>\][a-zA-Z]*                   {/*L*/
                                     ilink_set_resto(ilink, yytext+1);
                                     ilink_destroy(&ilink);
                                     BEGIN anterior;
                                     }

<ilink1,ilink2,ilink3>. ;

<*>. ;
<*>\n ;
%%
int yywrap(){
    //ilink_destroy();
    printf("DONE!\n");
    return 1;
}

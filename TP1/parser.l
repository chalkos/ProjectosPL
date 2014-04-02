/*%option debug*/

%x page
%x title
%x revision
%x timestamp
%x contributor
%x username
%x text

%x ilink1
%x ilink2
%x ilink3
%x ilink4
%x head1
%x head2
%x head3
%x head4
%x head5
%x head6


%{
#include "paginas.h"
#include "pagina.h"
#include "ilink.h"

ILink* ilink = NULL;
Pagina* pag = NULL;
Elemento* paginas = NULL;

%}
%%
    paginas = paginas_create();

"<page>"            {pag = pagina_create();
                     paginas_add(paginas, pag);
                     BEGIN page;
                    }
<page>"</page>"     BEGIN 0;

<page>"<title>"     BEGIN title;

<page>"<revision>"  BEGIN revision;

<title>"</title>"   BEGIN page;

<title>[^<]*        pagina_set_titulo(pag,yytext);

<revision>"<timestamp>"    BEGIN timestamp;
<revision>"<contributor>"  BEGIN contributor;
<revision>"</revision>"    BEGIN page;
<revision>\<text.*?\>      BEGIN text;

<timestamp>"</timestamp>"  BEGIN revision;
<timestamp>[^<]*           pagina_set_ultimaRevisao(pag, yytext);

<contributor>"<username>"      BEGIN username;
<contributor>"</contributor>"  BEGIN revision;

<username>"</username>"    BEGIN contributor;
<username>[^<]*            pagina_set_autor(pag, yytext);

<text>"</text>"     BEGIN revision;

<text>\n\=          BEGIN head1;
<text>\n\={2}       BEGIN head2;
<text>\n\={3}       BEGIN head3;
<text>\n\={4}       BEGIN head4;
<text>\n\={5}       BEGIN head5;
<text>\n\={6}       BEGIN head6;
<text>"[[File:"     ;/*ignorar [[ caso sejam ficheiros*/
<text>"[[Image:"    ;/*ignorar [[ caso sejam imagens*/
<text>"[[":?        BEGIN ilink1;

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

<ilink2>\([^\]\)\|]+\|              {/*EFH  */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     // deve adicionar ao texto, e nao meter em parenteses
                                     ilink_set_parenteses(ilink, yytext);
                                     BEGIN ilink3;
                                    }

<ilink2>\([^\]\)\|]+\]              {/*EFD  */
                                     yytext[ strlen(yytext)-1 ] = '\0';
                                     // deve adicionar ao texto, e nao meter em parenteses
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

<ilink4>\][a-zA-Z]*                 {/*L    */
                                     ilink_set_resto(ilink, yytext+1);
                                     //ilink_print(ilink);
                                     pagina_add_ilink(pag, ilink);
                                     BEGIN text;
                                    }

<ilink1,ilink2,ilink3>.             ;

<head1>[^\=]+                       pagina_add_seccao(pag, seccao_create(yytext, 1));
<head2>[^\=]+                       pagina_add_seccao(pag, seccao_create(yytext, 2));
<head3>[^\=]+                       pagina_add_seccao(pag, seccao_create(yytext, 3));
<head4>[^\=]+                       pagina_add_seccao(pag, seccao_create(yytext, 4));
<head5>[^\=]+                       pagina_add_seccao(pag, seccao_create(yytext, 5));
<head6>[^\=]+                       pagina_add_seccao(pag, seccao_create(yytext, 6));
<head1>\={1}                        BEGIN text;
<head2>\={2}                        BEGIN text;
<head3>\={3}                        BEGIN text;
<head4>\={4}                        BEGIN text;
<head5>\={5}                        BEGIN text;
<head6>\={4}                        BEGIN text;

<*>. ;
<*>\n ;
%%
int yywrap(){
    // escrever todas as infos
    paginas_print(paginas);

    // os destroys todos

    return 1;
}

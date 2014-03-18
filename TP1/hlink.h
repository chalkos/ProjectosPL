/*

Tipos de Links:

[Wikipedia:[[kingdom (biology)|]]
[[Seattle, Washington|]]
[[Wikipedia:Village pump|]]
[[Wikipedia:Manual of Style (headings)|]]
[[public transport]]ation

Em termos de variáveis:
[[special:view, moreLink]]moreView

Tipos de Special:
Category
Wikipedia
Help
Special
*/

#define HL_VIEW 0x1
#define HL_SPECIAL 0x2
#define HL_MORELINK 0x4
#define HL_MOREVIEW 0x8

typedef struct sHLink{
    char *view; // a parte que se lê
    char *special; // a parte antes dos :
    char *moreLink; // parte usada no link
    char *moreView; //parte usada no texto do link, depois de ]]
} HLink;

HLink hlink;

// atribuem partes do link
void hlink_set_view(char* viewPart);
void hlink_set_special(char* special);
void hlink_set_moreLink(char* moreLink);
void hlink_set_moreView(char* moreView);

// interpretar a ultima parte de um hlink
void hlink_got_ending(char* str);
void hlink_got_rename(char* str);

// mostra o que tem na variavel hlink
void hlink_print();

// informa o estado do hlink
unsigned int hlink_status();

// liberta memória associada ao hlink
void hlink_free_all();

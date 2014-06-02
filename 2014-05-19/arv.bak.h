#define PScons_arv 2000
#define PScons_arv_vazia 2001

typedef struct sArvore *Arvore;

struct sArvore {
    int flag;
    union {
        struct {
            int valor;
            Arvore left;
            Arvore right;
        } arv;
        struct {
        } vazia;
    } val;
};

Arvore cons_arv( Arvore a, :

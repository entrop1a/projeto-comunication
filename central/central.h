#include "../estrutura_central/client/client.h"
#include "../estrutura_central/server/server.h"

struct status{
    float b_level;
    //char *life;
};

struct element{
    struct status info;
    struct element *next;
};

struct fila{
    struct element *inicio;
    struct element *fim;
};

typedef struct status Status;
typedef struct element Element;
typedef struct fila Fila;

Fila* criar_fila();
void libera_fila(Fila* fi);
int tamanho_fila(Fila* fi);
int fila_vazia(Fila* fi);
int insere_fila(Fila* fi, Status dv);
int remove_fila(Fila* fi);
void imprime_fila(Fila* fi);
int verifica_limit(Fila* fi, float limit);
#include "central.h"

Fila* criar_fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->fim = NULL;
        fi->inicio = NULL;
    }
    return fi;
}

void libera_fila(Fila* fi){
    if(fi != NULL){
        Element* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->next;
            free(no);
        }
        free(fi);
    }
}

int tamanho_fila(Fila* fi){
    if(fi == NULL) return 0;
    
    int cont = 0;
    Element* no = fi->inicio;
    while(no != NULL){
        cont++;
        no = no->next;
    }
    return cont;
}

int fila_vazia(Fila* fi){
    if(fila_vazia(fi)) return 0;
    if(fi->inicio == NULL) return 1;
    return 0;
}

int insere_fila(Fila* fi, Status dv){
    if(fi == NULL) return 0;
    Element *no = (Element*) malloc(sizeof(Element));
    if(no == NULL) return 0;
    no->info = dv;
    no->next = NULL;
    if(fi->fim == NULL) fi->inicio = no;
    else fi->fim->next = no;
    fi -> fim = no;
    return 1;
}

int remove_fila(Fila* fi){
    if(fi == NULL) return 0;
    if(fi->inicio == NULL) return 0;
    Element *no = fi->inicio;
    fi->inicio = fi->inicio->next;
    if(fi->inicio == NULL) fi->fim = NULL;
    free(no);
    return 1;
}

void imprime_fila(Fila* fi){
    if(fi == NULL) printf("\n\tPilha vazia.\n");
    Element *no = fi->inicio;
    while(no != NULL){
        printf("Status de carga: %.3f\n", no->info.b_level);
        no = no -> next;
    }
}

int verifica_limit(Fila* fi, float limit){
    if(fi == NULL) printf("\n\tPilha vazia.\n");
    Element *no = fi->inicio;
    while(no != NULL){
        if(limit > (no->info.b_level) && (no->info.b_level) != 0.0) return 0;
        if((no->info.b_level) <= 0.0) return 2;
        no = no -> next;
    }
    return 1;
}
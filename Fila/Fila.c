//politica da fila: insere no final e remove do comeco
#include <stdio.h>
#include <stdlib.h>

void add();
void rem();
void show();
void liberar();

typedef struct {
        int valor;
        struct no *prox;
    } no;

/*struct lista{
    struct no *inicio;
    struct no *fim;
}*/

int main(){
    no *fila = malloc(sizeof(no));

    
}

void add(no **fila, int valor){
    if(fila->prox == NULL){
        fila.valor = valor;
    } else if(fila->prox != NULL){
                while(aux->prox != NULL){
                aux = aux->prox;
        }
    }
}

void rem(no **fila){
    if(*fila == NULL){
        return;
    no *aux = *fila;
    *fila = (*fila)->prox;
    free(*fila);
}

void show(no **fila){

}

void liberar(no **fila){
    while(*fila->prox != NULL){
        free
    }
}
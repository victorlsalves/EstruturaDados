//politica da fila: insere no final e remove do comeco (FIFO)
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char nome[50];
    struct no *ant;
    struct no *prox;
} no;

void inserir(no **f, char *nome)
{
    no *aux = malloc(sizeof(no));
    if(*f== NULL){
        aux->ant = NULL;
        aux->prox = NULL;
        strcpy(aux->nome, nome);
        *f = aux;
    } else {
        no *temp = *f;
        while (temp->prox == NULL)
        {
            
        }
        
    }
}
















int main(){
    no *fila = NULL;

    strcpy(fila->nome, "Ronald Reagan");







    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct demanda
{
    int tempo;
    char pessoa[50];
    int andar_origem;
    int andar_destino;
} demanda;

typedef struct no
{
    demanda d;
    struct no *ant;
    struct no *prox;
} no;

void inserir_comeco(no **l, demanda d)
{
    no *aux = malloc(sizeof(no));
    aux->d = d;
    aux->ant = NULL;
    aux->prox = *l;
    if(*l)
        (*l)->ant = aux; // caso não seja vazia
    *l = aux;
}

void inserir_final(no **l, demanda d)
{
    no *temp = *l;
    while (temp && temp->prox) //so sai qnd der null, ou seja, qnd achar o último nó
    {
        temp = temp->prox;
    }
    no *aux = malloc(sizeof(no));
    aux->d = d;
    aux->prox = NULL;
    aux->ant = temp;
    if(temp) // caso a lista não seja vazia
        temp->prox = aux;
    else
        *l = aux; // caso seja vazia
}

void alterar(no **l, char *pessoa, demanda d)
{
    no *aux = *l;
    if(aux == NULL){
        printf("\nNão há demandas na lista para alterar!\n");
        return;
    }
    while (aux != NULL && (strcmp(aux->d.pessoa, pessoa) != 0))
    {
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("\nA pessoa solicitada não possui uma demanda no momento!\n");
        return;
    }
    aux->d = d;
}

void remover(no **l, char *pessoa)
{
    no *aux = *l;
    if(aux == NULL){
        printf("\nNão há demandas na lista para remover!\n");
        return;
    }    
    while (aux != NULL && (strcmp(aux->d.pessoa, pessoa)) != 0)
    {
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("\nPessoa não encontrada!\n");
        return;
    }    
    if(aux->ant != NULL){
        aux->ant->prox = aux->prox;
    } else {
            (*l) = aux->prox;
    }        
    if(aux->prox != NULL)
        aux->prox->ant = aux->ant;
    free(aux);
}
void listar_demandas(no **l)
{
    int count = 0;
    no *aux = *l;
    while (aux != NULL)
    {
        printf("\nDemanda (%d): {Tempo:[%d] - Pessoa:[%s] - Andar de origem:[%d] - Andar de destino:[%d]}\n", (count + 1), aux->d.tempo, aux->d.pessoa, aux->d.andar_origem, aux->d.andar_destino);
        aux = aux->prox;
        count++;
    }
    if (count == 0)
        printf("\nA lista de demandas está vazia!\n");
}
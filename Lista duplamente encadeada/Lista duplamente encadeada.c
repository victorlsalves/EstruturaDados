#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    char nome[255];
} dados;

typedef struct no
{
    dados d;
    struct no *ant;
    struct no *prox;
} no;

void inserir_comeco(no **l, dados d)
{
    no *aux = malloc(sizeof(no));
    aux->d = d;
    aux->ant = NULL;
    aux->prox = *l;
    if(*l)
        (*l)->ant = aux; // caso não seja vazia
    *l = aux;
}

void inserir_final(no **l, dados d)
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

void alterar(no **l, int codigo, dados d)
{
    no *aux = *l;
    if(aux == NULL){
        printf("\nNão há elementos na lista para alterar!\n");
        return;
    }
    while (aux != NULL && (aux->d.codigo != codigo))
    {
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("\nNão foi encontrado o código anterior\n");
        return;
    }
    aux->d = d;
}

void remover(no **l, int codigo)
{
    no *aux = *l;
    if(aux == NULL){
        printf("\nNão há elementos na lista para remover!\n");
        return;
    }    
    while (aux != NULL && (aux->d.codigo != codigo))
    {
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("\nCódigo não encontrado!\n");
        return;
    }    
    if(aux->ant != NULL){
        aux->ant->prox = aux->prox;
    } else {
            (*l) = aux->prox;
    }        
    if(aux->prox != NULL)
        aux->prox->ant = aux-> ant;
    free(aux);
}
void listar_todos(no **l)
{
    int count = 0;
    no *aux = *l;
    while (aux != NULL)
    {
        printf("\n {Nome:[%s] - Código:[%d]}\n", aux->d.nome, aux->d.codigo);
        aux = aux->prox;
        count++;
    }
    if (count == 0)
        printf("\nA lista está vazia!\n");
}
int main()
{
    no *l = NULL;
    dados d1;
    dados d2;
    dados d3;
    
    d1.codigo = 1;
    strcpy(d1.nome, "Gus Fring");

    d2.codigo = 2;
    strcpy(d2.nome , "Walter White");

    d3.codigo = 3;
    strcpy(d3.nome , "Mossad");

    inserir_comeco(&l, d1);
    //listar_todos(&l);

    inserir_comeco(&l, d2);
    //listar_todos(&l);

    inserir_final(&l, d3);
    //listar_todos(&l);

    dados d4;
    d4.codigo = 4;
    strcpy(d4.nome, "Jesse Pinkman");
    alterar(&l, 3, d4);
    //listar_todos(&l);

    remover(&l, 1);
    //listar_todos(&l);
    remover(&l, 2);
    //listar_todos(&l);
    remover(&l, 4);
    listar_todos(&l);
    remover(&l, 3);
    listar_todos(&l);

    return 0;
}
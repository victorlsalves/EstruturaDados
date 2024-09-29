#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int capacidade;
    int tamanho;
    int *dados;
} lista;

void iniciar(lista *l, int capac)
{
    l->capacidade = capac;
    l->tamanho = 0;
    l->dados = malloc(capac * sizeof(int));
}

void finalizar(lista *l)
{
    free(l->dados);
}

int inserir_comeco(lista *l, int valor)
{
    if(l->tamanho == l->capacidade)
        return printf("\nA lista está cheia!\n");
    for (int i = l->tamanho - 1; i >= 0; i--)
        *(l->dados + i + 1) = *(l->dados + i);
    *(l->dados) = valor;
    l->tamanho++;
}

int inserir_final(lista *l, int valor)
{
    if (l->tamanho == l->capacidade)
        return printf("\nA lista está cheia!\n");
    *(l->dados + l->tamanho) = valor;
    l->tamanho++;
}

int buscar(lista *l, int valor)
{
    if(l->tamanho == 0)
        return printf("\nNão há elemento na lista, busca cancelada.\n");
    for (int i = 0; i < l->tamanho; i++)
    {
        if(*(l->dados + i) == valor)
            return *(l->dados + i);
    }
    printf("\nO valor não está na lista!\n");
    return -1;
}

int alterar(lista *l, int valor, int novo_valor)
{
    int count = 0;
    if (l->tamanho == 0)
        return printf("\nA lista está vazia! Não há elemento para alterar.\n");
    for (int i = 0; i < l->tamanho; i++)
    {
        if(*(l->dados + i) == valor)
        {
            *(l->dados + i) = novo_valor;
            count++;
        }
    }
    if(count == 0)
        return printf("\nO valor não foi encontrado na lista!\n");
}

int remover(lista *l, int valor)
{
    int count = 0;
    if(l->tamanho == 0)
        return printf("\nNão há elemento na lista para remover!\n");
    for (int i = l->tamanho - 1; i >= 0; i--)
    {
        if(*(l->dados + i) == valor)
        {
            for (int j = i; j < l->tamanho - 1; j++)
                *(l->dados + j) = *(l->dados + j + 1);
            count++;
            l->tamanho--;    
        }
    }
    if (count == 0)
        return printf("\nO valor para remover não foi encontrado na lista!\n");
}

int listar_todos(lista *l)
{
    if(l->tamanho == 0)
        return printf("A lista está vazia!\n");
    for (int i = 0; i < l->tamanho; i++)
        printf("[ %d ] \t", *(l->dados + i));
    printf("\n");
}

int main()
{
    lista l1;
    int busca = -1;
    
    iniciar(&l1, 10);
    alterar(&l1, 888, 888);
    buscar(&l1, 23);
    listar_todos(&l1);
    remover(&l1, 23);
    inserir_comeco(&l1, 23);
    busca = buscar(&l1, 23);
    printf("%d",busca);
    busca = buscar(&l1, 12);
    printf("%d",busca);

    finalizar(&l1);
}
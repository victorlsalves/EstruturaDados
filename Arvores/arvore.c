#include <stdio.h>
#include <stdlib.h>

// código para árvores em si

struct noa 
{
    int valor;
    struct noa *esq;
    struct noa *dir;
};

typedef struct noa noa;

// inserção tem 2 casos a avaliar
// 1o - quando o nó é nulo
// 2o - quando não é nulo
noa *a_inserir_rr(noa *raiz, int valor) // versão com retorno do nó
{
    if(raiz == NULL)
    {
        noa *aux = malloc(sizeof(noa));
        aux->valor = valor;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    }

    if(valor > raiz->valor)
        raiz->dir = a_inserir_rr(raiz->dir, valor);
    else if(valor < raiz->valor)
        raiz->esq = a_inserir_rr(raiz->esq, valor);
    return raiz;
}

void a_inserir_pp(noa **raiz, int valor) // função sem retorno, usando ponteiro para ponteiro
{
    if(*raiz == NULL)
    {
        noa *aux = malloc(sizeof(noa));
        aux->valor = valor;
        aux->esq = NULL;
        aux->dir = NULL;
        *raiz = aux;
        return;
    }

    noa *r = *raiz;
    if(valor > r->valor)
        a_inserir_pp(&(r->dir), valor);
    else if(valor < r->valor)
        a_inserir_pp(&(r->esq), valor);
}

noa *a_buscar(noa *raiz, int valor)
{
    if(raiz == NULL) // se não está na árvore
        return NULL;
    
    if(valor > raiz->valor) // se tem que andar na árvore
    {
        raiz->dir = a_buscar(raiz->dir, valor);
        return raiz;
    } 
    else if(valor < raiz->valor)
    {
        raiz->esq = a_buscar(raiz->esq, valor);
        return raiz;
    }
    return raiz;
}

// função para encontrar o menor valor na subárvore
noa *a_minimo(noa *raiz)
{
    while(raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

// função para remover um nó da árvore de busca binária
noa *a_remover(noa *raiz, int valor)
{
    if(raiz == NULL) // caso base: árvore vazia
        return raiz;

    // percorre a árvore para encontrar o nó a ser removido
    if(valor < raiz->valor)
        raiz->esq = a_remover(raiz->esq, valor);
    else if(valor > raiz->valor)
        raiz->dir = a_remover(raiz->dir, valor);
    else
    {
        // caso 1: nó com apenas um filho ou nenhum
        if(raiz->esq == NULL)
        {
            noa *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if(raiz->dir == NULL)
        {
            noa *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // caso 2: nó com dois filhos
        // encontra o sucessor (menor valor na subárvore à direita)
        noa *temp = raiz->dir;
        while(temp->esq != NULL){
            temp = temp->esq;
        }
        // copia o valor do sucessor para este nó
        raiz->valor = temp->valor;

        // remove o sucessor
        raiz->dir = a_remover(raiz->dir, temp->valor);
    }
    return raiz;
}

void a_pre_ordem(noa *raiz)
{
    if(raiz == NULL)
        return;
    printf("%d ", raiz->valor);
    a_pre_ordem(raiz->esq);
    a_pre_ordem(raiz->dir);
}

void a_em_ordem(noa *raiz)
{
    if(raiz == NULL)
        return;
    a_em_ordem(raiz->esq);
    printf("%d ", raiz->valor);
    a_em_ordem(raiz->dir);
}

void a_pos_ordem(noa *raiz)
{
    if(raiz == NULL)
        return;
    a_pos_ordem(raiz->esq);
    a_pos_ordem(raiz->dir);
    printf("%d ", raiz->valor);
}

int main() 
{
    noa *raiz = NULL;

    raiz = a_inserir_rr(raiz, 50);
    raiz = a_inserir_rr(raiz, 25);
    raiz = a_inserir_rr(raiz, 80);
    raiz = a_inserir_rr(raiz, 20);
    raiz = a_inserir_rr(raiz, 30);
    raiz = a_inserir_rr(raiz, 60);
    raiz = a_inserir_rr(raiz, 90);

    printf("pre-ordem: ");
    a_pre_ordem(raiz);
    printf("\n");
    printf("em-ordem: ");
    a_em_ordem(raiz);
    printf("\n");
    printf("pos-ordem: ");
    a_pos_ordem(raiz);
    printf("\n");

    // Remover o nó com valor 50
    raiz = a_remover(raiz, 50);

    printf("Após remover 50:\n");
    printf("pre-ordem: ");
    a_pre_ordem(raiz);
    printf("\n");
    printf("em-ordem: ");
    a_em_ordem(raiz);
    printf("\n");
    printf("pos-ordem: ");
    a_pos_ordem(raiz);
    printf("\n");

    return 0;
}

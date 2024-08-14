#include <stdio.h>
#include <stdlib.h>
#define capac 10

struct lista
{
int capacidade;
int tamanho;
int conjunto; // se tem elementos repetidos ou nao
int *dados[capac]; // vetor de ponteiros
};


void iniciar(struct lista *l)
{
l->conjunto = 0; // pode ter elementos repetidos
l->capacidade = capac;
l->tamanho = 0;
for (int i = 0; i < capac; ++i) {
l->dados[i] = NULL;
}

}

void finalizar(struct lista *l){
for (int i = 0; i < capac; ++i) {
if(l->dados[i] != NULL)
free(l->dados[i]);
}
}

int buscar(struct lista *l, int valor)
{
for (int i = 0; i < l->tamanho; ++i) {
if(*l->dados[i] == valor)
return i;
}
return printf("O valor não está na lista!");
}

int inserir_comeco(struct lista *l, int valor)
{
if(l->tamanho == l->capacidade)
return -1; // não tem memoria para inserir
if(l->conjunto && buscar(l, valor) != -1) {
return -2; // não pode inserir porque já tem o elemento na lista
}

for (int i = l->tamanho - 1; i >= 0 ; i--) {
// 4 3 2 1
l->dados[i+1] = l->dados[i];
}
l->dados[0] = malloc(sizeof(int));
*l->dados[0] = valor;
l->tamanho++;
}

int inserir_final(struct lista *l, int valor)
{
if(l->tamanho == l->capacidade)
return -1; // não tem memoria para inserir
if(l->conjunto && buscar(l, valor) != -1){
return -2; // não pode inserir porque já tem o elemento na lista
}

l->dados[l->tamanho] = malloc(sizeof(int));
*l->dados[l->tamanho] = valor;
l->tamanho++;
}

int alterar(struct lista *l, int valor, int novo_valor)
{
int index = buscar(l, valor);
if(index == -1)
return -1; // não tem valor na lista, então não tem o que mudar
*l->dados[index] = novo_valor;
}

int excluir(struct lista *l, int valor)
{
int index = buscar(l, valor);
if(index == -1)
return -1; // não tem valor na lista, então não tem o que mudar
free(l->dados[index]);

for (int i = index; i < l->tamanho - 1; ++i)
l->dados[i] = l->dados[i + 1];

l->tamanho--;
l->dados[l->tamanho] = NULL;
}

void listar_todos(struct lista *l)
{
printf("[");
for (int i = 0; i < l->tamanho; ++i) {
printf("%d", *l->dados[i]);
if(i != l->tamanho - 1)
printf(", ");
}
printf("]\n");
}

int main() {

struct lista l1;
iniciar(&l1);

buscar(&l1,2);

return 0;
}
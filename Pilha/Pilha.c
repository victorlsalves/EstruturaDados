#include <stdio.h>
#include <stdlib.h>

void inserir_final();
void remover_final();

typedef struct
{
   int codigo;
   char nome[255];
} dados;

typedef struct
{
    dados d;
    no *prox;
    no *ant;
} no;



int main(){
    


}

void inserir_final(pilha *p, int valor){
    if(p->topo + 1 == p->capacidade){
        printf("a pilha esta cheia");
        return;
    } else if(){

    }
}

void remover_final(){

}
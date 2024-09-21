#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "demanda.h"

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

void alterar(no **l, int pessoa, demanda d)
{
    no *aux = *l;
    if(aux == NULL){
        printf("\nNão há demandas na lista para alterar!\n");
        return;
    }
    while (aux != NULL && aux->d.n_pessoa != pessoa)
    {
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("\nA pessoa solicitada não possui uma demanda no momento!\n");
        return;
    }
    aux->d = d;
}

void remover(no **l, int pessoa)
{
    no *aux = *l;
    if(aux == NULL){
        printf("\nNão há demandas na lista para remover!\n");
        return;
    }    
    while (aux != NULL && aux->d.n_pessoa != pessoa)
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
        printf("\nDemanda (%d): {tempo_recebido:[%d] - Pessoa:[%d] - Status:[%c] - Andar de origem:[%d] - Andar de destino:[%d]}\n", (count + 1), aux->d.tempo_recebido, aux->d.n_pessoa, aux->d.status, aux->d.andar_origem, aux->d.andar_destino);
        aux = aux->prox;
        count++;
    }
    if (count == 0)
        printf("\nA lista de demandas está vazia!\n");
}

void ordenar_demandas(no **l, int crescente) // crescente eh uma variavel que, se for 1, faz a funcao ordenar em ordem crescente e, se for 0, a funcao ordena em ordem decrescente
{
    if (*l == NULL)
    {
        printf("\nA lista de demandas está vazia!\n");
        return;
    }
    int trocou; // variavel de controle: se for 0, n trocou nd e o laco para, se for 1, trocou e o laco continua
    no *aux;
    do
    {
        trocou = 0;
        aux = *l;
        while (aux->prox != NULL)
        {
            if ((crescente && aux->d.andar_origem > aux->prox->d.andar_origem) || (!crescente && aux->d.andar_origem < aux->prox->d.andar_origem)) // verifica se a ordem está errada, comparando o andar de origem
            {
                demanda temp = aux->d; // troca as demandas
                aux->d = aux->prox->d;
                aux->prox->d = temp;
                trocou = 1;
            }
            aux = aux->prox;
        }
    } while (trocou);
}

void preencher_novas_demandas(no **l, char string[])
{
    demanda nova_demanda;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if(string[i] == 'T' && string[i-1] == ' ' && isdigit(string[i+1]))
        {
            for (int j = i; string[j] != ' '; j++)
            {
                if(isdigit(string[j]) && string[j-1] == 'T' && string[j+1] == '_')
                {
                    nova_demanda.tempo_recebido = retornaUmNumeroInteiro(string[j]); //preencher o tempo de 1 dígito da demanda
                }
                else if(string[j-1] == 'T' && isdigit(string[j]) && isdigit(string[j+1]))
                {
                    nova_demanda.tempo_recebido = retornaDoisNumerosInteiro(string[j], string[j+1]); //preencher o tempo de 2 dígitos da demanda
                }
                else if(string[j] == 'P' && isdigit(string[j+1]) && isdigit(string[j+2]))
                {
                    nova_demanda.n_pessoa = retornaDoisNumerosInteiro(string[j+1], string[j+2]); //preencher o número da pessoa da demanda
                }
                else if(string[j] == 'S' && string[j-1] == '_' && string[j+1] == '_')
                {
                    nova_demanda.status = string[j]; //preencher o status de movimento da demanda com subindo
                }
                else if(string[j] == 'D' && string[j-1] == '_' && string[j+1] == '_')
                {
                    nova_demanda.status = string[j]; //preencher o status de movimento da demanda com descendo
                }
                else if(string[j-1] == '_' && isdigit(string[j]) && string[j+1] == '_')
                {
                    nova_demanda.andar_origem = retornaUmNumeroInteiro(string[j]); //preencher andar de origem com 1 digito
                }
                else if(string[j-1] == '_' && isdigit(string[j]) && isdigit(string[j+1]) && string[j+2] == '_')
                {
                    nova_demanda.andar_origem = retornaDoisNumerosInteiro(string[j], string[j+1]); //preencher andar de origem com 2 dígitos
                }
                else if(string[j-1] == '_' && string[j] == 'T' && string[j+1] == '_')
                {
                    nova_demanda.andar_origem = 0; //preencher andar de origem como térreo
                }
                else if(string[j-1] == '_' && isdigit(string[j]) && (string[j+1] == ' ' || string[j+1] == '\0'))
                {
                    nova_demanda.andar_destino = retornaUmNumeroInteiro(string[j]); //preencher andar de destino com 1 digito
                }
                else if(string[j-1] == '_' && isdigit(string[j]) && isdigit(string[j+1]) && (string[j+2] == ' ' || string[j+2] == '\0'))
                {
                    nova_demanda.andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]); //preencher andar de destino com 2 digitos
                }
                else if(string[j-1] == '_' && string[j] == 'T' && (string[j+1] == ' ' || string[j+1] == '\0'))
                {
                    nova_demanda.andar_destino = 0; //preencher andar de destino como térreo
                }
            }
            inserir_final(l, nova_demanda); // tirei *nova_demanda e deixei somente nova_demanda pq nas funcoes de inserir ja tem um malloc, ent teria q mudar ela se fosse pra passar um ponteiro
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "demanda.h"
#include "utils.h"

typedef struct elevador
{
    int num_elev;
    char status;
    no *lista_demandas;
    int tempo_corrido;
    int andar_atual;
    int andares_max;
} elevador;

typedef struct no_elevador //aqui eh a lista de elevadores, assim como a struct de demandas tem um nó que serve pra ser a lista de demandas
{
    elevador e;
    struct no_elevador *ant;
    struct no_elevador *prox;
} no_elevador;

void criar_elevador(no_elevador **elevadores, elevador *novo_elevador)
{
    no_elevador *aux = *elevadores;
    aux = malloc(sizeof(no_elevador));
    aux->e.num_elev = novo_elevador->num_elev;
    aux->e.status = novo_elevador->status;
    aux->e.lista_demandas = novo_elevador->lista_demandas;
    aux->e.tempo_corrido = novo_elevador->tempo_corrido;
    aux->e.andar_atual = novo_elevador->andar_atual;
    aux->e.andares_max = novo_elevador->andares_max;
    aux->ant = NULL;
    aux->prox = *elevadores;
        if(*elevadores)
            (*elevadores)->ant = aux; // caso não seja vazia
    *elevadores = aux;
}

void inserir_demanda(elevador **e, demanda d)
{
    no *temp = (*e)->lista_demandas;
    while (temp && temp->prox) //so sai qnd der null, ou seja, qnd achar o último nó
    {
        temp = temp->prox;
    }
    elevador *aux = malloc(sizeof(elevador));
    aux->lista_demandas->d = d;
    aux->lista_demandas->prox = NULL;
    aux->lista_demandas->ant = temp;
    if((*e)->lista_demandas) // caso o elevador tenha alguma demanda
        (*e)->lista_demandas->prox = aux->lista_demandas->ant;
    else
        *e = aux; // caso elevador esteja sem demanda
}

int retornaNumAndarMaxElevador(char string[])
{
    int qtd_max;
    for(int i = 0; string[i] != ' '; i++)
    {
        if(string[i-1] == '_' && isdigit(string[i]) && string[i+1] == ' ')
        {
            qtd_max = retornaUmNumeroInteiro(string[i]);
        }
        else if(isdigit(string[i]) && isdigit(string[i+1]) && string[i+2] == ' ')
        {
            qtd_max = retornaDoisNumerosInteiro(string[i], string[i+1]);
        }
    }    
    return qtd_max;
}

void preencher_dados_elevador(no_elevador **e, char string[])
{
    elevador *novo_elev;
    for(int i = 0; string[i] != '\0'; i++)
    {
        if(string[i] == 'E'){
            novo_elev = malloc(sizeof(elevador));
            for(int j = i; string[j] != ' '; j++)
            {
                if(isdigit(string[j]) && string[j-1] == 'E')
                {
                    novo_elev->andares_max = retornaNumAndarMaxElevador(string);
                    novo_elev->num_elev = retornaUmNumeroInteiro(string[j]); //numero do elevador
                }
                else if(string[j-1] == '_' && string[j] == 'T' && string[j+1] == '_')
                {
                    novo_elev->andar_atual = 0; //andar atual como Térreo
                }
                else if(string[j-1] == '_' && isdigit(string[j]) && isdigit(string[j+1]))
                {
                    novo_elev->andar_atual = retornaDoisNumerosInteiro(string[j], string[j+1]); //andar atual
                }
                else if(string[j] == 'D' && string[j+1] == '_')
                {
                    novo_elev->status = string[j]; //status descendo
                }
                else if(string[j] == 'S' && string[j+1] == '_')
                {
                    novo_elev->status = string[j]; //status subindo
                }
                else if(isdigit(string[j]) && isdigit(string[j+1]) && (string[j+2] == ',' || string[j+2] == ' '))
                {
                    //preencher demanda de andar >= 10
                    //novo_elev->demandas = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    demanda nova_demanda;
                    nova_demanda.andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    inserir_demanda(&novo_elev, nova_demanda);
                }
                else if(isdigit(string[j]) && !isdigit(string[j-1]) && (string[j+1] == ',' || string[j+1] == ' ')){
                    //preencher demandar de andar < 10
                    //novo_elev->demandas = retornaUmNumeroInteiro(string[j]);
                    demanda nova_demanda;
                    nova_demanda.andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    inserir_demanda(&novo_elev, nova_demanda);
                }
                else if(string[j] == 'T' && (string[j+1] == ',' || string[j+1] == ' ')){
                    //retorna o térreo = 0;
                    //novo_elev->demandas = 0;
                    demanda nova_demanda;
                    nova_demanda.andar_destino = 0;
                    inserir_demanda(&novo_elev, nova_demanda);
                }
            }
            criar_elevador(&(*e), novo_elev); //funcaoInserir/CriarElevador(listaElevador(elevador), novo_elev(elevador));
            /*
            printf("---------------\n");
            printf("Número do andar: %d\n", elev->num_elev);
            printf("Número do andares máximo: %d\n", elev->andares_max);
            printf("Andar atual: %d\n", elev->andar_atual);
            printf("Status do elevador: %c\n", elev->status);
            //inserir uma por uma as demandas, e não de uma vez.
            printf("Demanda: %d\n", elev->demandas);
            free(elev);
            */
        }
    }
}


























// inserir recebe struct elevador
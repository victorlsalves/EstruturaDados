#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "demanda.h"
#include "utils.h"
#include "elevador.h"
#include <unistd.h>

// typedef struct elevador
// {
//     int num_elev;
//     char status;
//     no *lista_demandas;
//     int tempo_corrido;
//     int andar_atual;
//     int andares_max;
// } elevador;

// //aqui eh a lista de elevadores, assim como a struct de demandas tem um nó que serve pra ser a lista de demandas
// typedef struct no_elevador 
// {
//     elevador e;
//     struct no_elevador *ant;
//     struct no_elevador *prox;
// } no_elevador;

void criar_elevador(no_elevador **elevadores, elevador novo_elevador)
{
    no_elevador *aux = *elevadores;
    aux = malloc(sizeof(no_elevador));

    aux->e = novo_elevador;
    // aux->e.num_elev = novo_elevador->num_elev;
    // aux->e.status = novo_elevador->status;
    // aux->e.lista_demandas = novo_elevador->lista_demandas;
    // aux->e.tempo_corrido = novo_elevador->tempo_corrido;
    // aux->e.andar_atual = novo_elevador->andar_atual;
    // aux->e.andares_max = novo_elevador->andares_max;
    aux->ant = NULL;
    aux->prox = *elevadores;
    if(*elevadores)
        (*elevadores)->ant = aux; // caso não seja vazia
    *elevadores = aux;
}

void inserir_demanda(elevador **e, demanda d, int flag_demanda)
{
    if(flag_demanda == 0){
        (*e)->lista_demandas = NULL;
    }
    
    // Aloca memória para o novo nó de demanda
    no *nova_demanda = malloc(sizeof(no));
    if (nova_demanda == NULL) {
        printf("Erro ao alocar memória para nova demanda.\n");
        return;
    }

    // Preenche os dados da nova demanda
    nova_demanda->d = d;
    nova_demanda->prox = NULL;
    nova_demanda->ant = NULL;

    // Verifica se o elevador já tem uma lista de demandas
    if ((*e)->lista_demandas == NULL) {
        // Caso a lista de demandas esteja vazia, adiciona a nova demanda como a primeira
        (*e)->lista_demandas = nova_demanda;
    } else {
        // Caso a lista já tenha demandas, percorre até o último nó
        no *temp = (*e)->lista_demandas;

        while (temp->prox != NULL) { // Percorre até encontrar o último nó
            temp = temp->prox;
        }

        // Adiciona a nova demanda no final da lista
        temp->prox = nova_demanda;
        nova_demanda->ant = temp;
    }
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
    demanda *nova_demanda;

    //no *demandas = NULL;
    //demanda *nova_demanda;
    for(int i = 0; string[i] != '\0'; i++)
    {
        if(string[i] == 'E'){
            int flag_demanda = 0;
            novo_elev = malloc(sizeof(elevador));
            nova_demanda = malloc(sizeof(demanda));
            //nova_demanda = malloc(sizeof(demanda));
            //demanda demanda_nova[10];
            //int qta_demandas = 0;

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
                    //demanda nova_demanda;
                    nova_demanda->andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    inserir_demanda(&novo_elev, *nova_demanda, flag_demanda);
                    flag_demanda++;
                    //inserir_final(&demandas, *nova_demanda);
                }
                else if(isdigit(string[j]) && !isdigit(string[j-1]) && (string[j+1] == ',' || string[j+1] == ' ')){
                    //preencher demandar de andar < 10
                    //novo_elev->demandas = retornaUmNumeroInteiro(string[j]);
                    //demanda nova_demanda;
                    nova_demanda->andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    inserir_demanda(&novo_elev, *nova_demanda, flag_demanda);
                    flag_demanda++;

                    //inserir_final(&demandas, *nova_demanda);
                }
                else if(string[j] == 'T' && (string[j+1] == ',' || string[j+1] == ' ')){
                    //retorna o térreo = 0;
                    //novo_elev->demandas = 0;
                    //demanda nova_demanda;
                    nova_demanda->andar_destino = 0;
                    inserir_demanda(&novo_elev, *nova_demanda, flag_demanda);
                    flag_demanda++;
                    //inserir_final(&demandas, *nova_demanda);
                }
            }
            criar_elevador(e, *novo_elev); //funcaoInserir/CriarElevador(listaElevador(elevador), novo_elev(elevador));
            
        }
    }
}

void mostrar_elevadores(no_elevador *elev, int tempo){
    no_elevador *aux_elev = elev;

    while (aux_elev != NULL)
    {
        printf("\nTempo atual: %d\n", tempo);
        printf("Elevador E%d\n", aux_elev->e.num_elev);
        printf("Status: %c\n", aux_elev->e.status);
        printf("Andar atual: %d\n", aux_elev->e.andar_atual);
        no *aux_dem = aux_elev->e.lista_demandas;
        while (aux_dem != NULL)
        {
            printf("\nDemanda | Andar destino: %d",aux_dem->d.andar_destino);
            aux_dem = aux_dem->prox;
        }
        
        aux_elev = aux_elev->prox;
        printf("\n");
    }
    
}

void alterar_andar_atual(no_elevador **elevador){
    no_elevador *aux = *elevador;
    while (aux != NULL)
    {
        if(aux->e.status == 'S'){

            if(aux->e.andar_atual < aux->e.andares_max){ //se andar atual for menor que andar máximo
                aux->e.andar_atual++; //subindo para o andar máximo
            }
            else if(aux->e.andar_atual == aux->e.andares_max){ //se o andar atual for igual ao andar máximo, altera o status para D e decrementa o andar atual
                aux->e.status = 'D';
                aux->e.andar_atual--;
            }
        }
        else if(aux->e.status == 'D'){
            if(aux->e.andar_atual > 0){ //verifica se o andar atual for maior que térreo (0)
                aux->e.andar_atual--; //descendo
            }
            else if(aux->e.andar_atual == 0){ //se chegar no térreo ele muda o status pra subindo e incrementa o andar atual
                aux->e.status = 'S';
                aux->e.andar_atual++;
            }
        }

        aux = aux->prox;
    }
}

void atribuir_nova_demanda(no_elevador **elevador, no **demanda, int tempo){
    no_elevador *aux_elev = *elevador;
    no *aux_deman = *demanda;
    while (aux_elev != NULL)
    {
        while (aux_deman != NULL)
        {
            if(aux_elev->e.andar_atual == aux_deman->d.andar_origem){
                if(tempo >= aux_deman->d.tempo_recebido && aux_deman->d.status == aux_elev->e.status){
                    inserir_final(&(aux_elev->e.lista_demandas), aux_deman->d);
                }
            }
            aux_deman = aux_deman->prox;
        }
        aux_elev = aux_elev->prox;
    }
}

void movimentar_elevador(no_elevador *elevador, no *demandas){
    int tempo = 1;
    
    while (1)
    {
        atribuir_nova_demanda(&elevador, &demandas, tempo);
        mostrar_elevadores(elevador, tempo);
        alterar_andar_atual(&elevador);
        sleep(1);
        tempo++;
    }
}

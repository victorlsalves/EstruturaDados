#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "demanda.h"
#include "utils.h"
#include "elevador.h"
#include <unistd.h>

void criar_elevador(no_elevador **elevadores, elevador novo_elevador)
{
    no_elevador *aux = *elevadores;
    aux = malloc(sizeof(no_elevador));
    aux->e = novo_elevador;
    aux->ant = NULL;
    aux->prox = *elevadores;
    if(*elevadores)
        (*elevadores)->ant = aux; //caso não seja vazia
    *elevadores = aux;
}

void inserir_demanda(elevador **e, demanda d, int flag_demanda)
{
    if(flag_demanda == 0){
        (*e)->lista_demandas = NULL;
    }
    no *nova_demanda = malloc(sizeof(no));
    if (nova_demanda == NULL) {
        printf("Erro ao alocar memória para nova demanda.\n");
        return;
    }
    nova_demanda->d = d;
    nova_demanda->prox = NULL;
    nova_demanda->ant = NULL;
    if ((*e)->lista_demandas == NULL) //caso a lista de demandas esteja vazia, adiciona a nova demanda como a primeira
    {
        (*e)->lista_demandas = nova_demanda;
    } else {
        no *temp = (*e)->lista_demandas; 
        while (temp->prox != NULL) //caso a lista já tenha demandas, percorre até o último nó
        {
            temp = temp->prox;
        }
        temp->prox = nova_demanda; //adiciona a nova demanda no final da lista
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
    for(int i = 0; string[i] != '\0'; i++)
    {
        if(string[i] == 'E'){
            int flag_demanda = 0;
            novo_elev = malloc(sizeof(elevador));
            nova_demanda = malloc(sizeof(demanda));
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
                else if(isdigit(string[j]) && isdigit(string[j+1]) && (string[j+2] == ',' || string[j+2] == ' ')) //preencher demanda de andar >= 10
                {
                    nova_demanda->andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    inserir_demanda(&novo_elev, *nova_demanda, flag_demanda);
                    flag_demanda++;
                }
                else if(isdigit(string[j]) && !isdigit(string[j-1]) && (string[j+1] == ',' || string[j+1] == ' ')) //preencher demandar de andar < 10
                {
                    nova_demanda->andar_destino = retornaDoisNumerosInteiro(string[j], string[j+1]);
                    inserir_demanda(&novo_elev, *nova_demanda, flag_demanda);
                    flag_demanda++;
                }
                else if(string[j] == 'T' && (string[j+1] == ',' || string[j+1] == ' ')) //retorna o térreo = 0;
                {
                    nova_demanda->andar_destino = 0;
                    inserir_demanda(&novo_elev, *nova_demanda, flag_demanda);
                    flag_demanda++;
                }
            }
            novo_elev->qtd_andares_percorridos = 0;
            novo_elev->tempo_deslocamento = 0;
            criar_elevador(e, *novo_elev); // cria um elevador passando *novo_elev
        }
    }
}

void mostrar_elevadores(no_elevador *elev, int tempo)
{
    no_elevador *aux_elev = elev;
    while (aux_elev != NULL)
    {
        printf("\nTempo atual: %d\n", tempo);
        printf("Elevador E%d\n", aux_elev->e.num_elev);
        printf("Status: %c\n", aux_elev->e.status);
        printf("Andar atual: %d\n", aux_elev->e.andar_atual);
        printf("Quantidade de andares percorridos: %d\n", aux_elev->e.qtd_andares_percorridos);
        printf("Tempo de deslocamento: %d", aux_elev->e.tempo_deslocamento);
        no *aux_dem = aux_elev->e.lista_demandas;
        printf("\nDemanda | Andar destino: ");
        while (aux_dem != NULL)
        {
            printf("[%d] ",aux_dem->d.andar_destino);
            aux_dem = aux_dem->prox;
        }
        aux_elev = aux_elev->prox;
        printf("\n");
    }
    printf("\n----------------------------------------------\n");
}

void alterar_andar_atual(no_elevador **elevador, no *demandas)
{
    no_elevador *aux = *elevador;
    while (aux != NULL)
    {
        if(aux->e.status == 'S')
        {
            if(aux->e.andar_atual < aux->e.andares_max && (demandas || aux->e.lista_demandas)) //se andar atual for menor que andar máximo
            { 
                aux->e.andar_atual++; //subindo para o andar máximo
                aux->e.qtd_andares_percorridos++;
                aux->e.tempo_deslocamento++;
            }
            else if(aux->e.andar_atual == aux->e.andares_max && (demandas || aux->e.lista_demandas)) //se o andar atual for igual ao andar máximo, altera o status para D e decrementa o andar atual
            {
                aux->e.status = 'D';
                aux->e.andar_atual--;
                aux->e.qtd_andares_percorridos++;
                aux->e.tempo_deslocamento++;
                ordenar_demandas(&(aux->e.lista_demandas), 0);
            }
        }
        else if(aux->e.status == 'D')
        {
            if(aux->e.andar_atual > 0 && (demandas || aux->e.lista_demandas)) //verifica se o andar atual for maior que térreo (0)
            {
                aux->e.andar_atual--; //descendo
                aux->e.qtd_andares_percorridos++;
                aux->e.tempo_deslocamento++;
            }
            else if(aux->e.andar_atual == 0 && (demandas || aux->e.lista_demandas)) //se chegar no térreo ele muda o status pra subindo e incrementa o andar atual
            {
                aux->e.status = 'S';
                aux->e.andar_atual++;
                aux->e.qtd_andares_percorridos++;
                aux->e.tempo_deslocamento++;
                ordenar_demandas(&(aux->e.lista_demandas), 1);
            }
        }
        aux = aux->prox;
    }
}

void atribuir_nova_demanda(no_elevador **elevador, no **demanda, int tempo) // atribui novas demandas da lista geral à lista de demandas dos elevadores e as remove da lista geral
{
    no_elevador *aux_elev = *elevador;
    while (aux_elev != NULL)
    {
        no *aux_deman = *demanda;
        while (aux_deman != NULL)
        {
            if(aux_elev->e.andar_atual == aux_deman->d.andar_origem)
            {
                if(tempo >= aux_deman->d.tempo_recebido)
                {
                    inserir_final(&(aux_elev->e.lista_demandas), aux_deman->d);
                    remover(demanda, aux_elev->e.andar_atual, tempo);
                }
            }
            aux_deman = aux_deman->prox;
        }
        aux_elev = aux_elev->prox;
    }
}

void desembarque_andar_destino(no_elevador **elevador, int tempo)
{
    no_elevador *aux_elev = *elevador;
    while (aux_elev != NULL)
    {
        no *aux_deman_elev = aux_elev->e.lista_demandas;
        while (aux_deman_elev != NULL)
        {
            if(aux_elev->e.andar_atual == aux_deman_elev->d.andar_destino) // compara andar atual com os andares de destino da lista de demandas do elevador
            {
                remover_destino(&(aux_elev->e.lista_demandas), aux_deman_elev->d.andar_destino); // pessoa desembarca no andar e ele eh removido da lista de demandas do elevador
            }
            aux_deman_elev = aux_deman_elev->prox;
        }
        aux_elev = aux_elev->prox;
    }
}

int contador_demandas_elev(no_elevador *elev) // retorna a quantidade de demandas nos elevadores
{
    no_elevador *aux_elev = elev;
    int contador = 0;
    while (aux_elev != NULL)
    {
        no *aux_dem = aux_elev->e.lista_demandas;
        while (aux_dem != NULL)
        {
            contador++;
            aux_dem = aux_dem->prox;
        }
        aux_elev = aux_elev->prox;
    }
    return contador;
}

void retornar_resumo_deslocamento(no_elevador *e)
{
    no_elevador *aux = e;
    int tempo_total = 0;
    int deslocamento_total = 0;
    while (aux != NULL)
    {
        tempo_total += aux->e.tempo_deslocamento;
        deslocamento_total += aux->e.qtd_andares_percorridos;
        aux = aux->prox;
    }
    printf("\n{Tempo total dos elevadores: [%d] - Quantidade de andares percorridos pelos elevadores: [%d]}\n", tempo_total, deslocamento_total);
}

void movimentar_elevador(no_elevador *elevador, no *demandas)
{
    int tempo = 1;
    while (demandas || contador_demandas_elev(elevador))
    {
        listar_demandas(&demandas);
        atribuir_nova_demanda(&elevador, &demandas, tempo);
        desembarque_andar_destino(&elevador, tempo);
        mostrar_elevadores(elevador, tempo);
        alterar_andar_atual(&elevador, demandas);
        sleep(1);
        tempo++;
    }
    retornar_resumo_deslocamento(elevador);
}
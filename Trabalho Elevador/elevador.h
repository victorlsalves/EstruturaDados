#include <stdio.h>
#include "demanda.h"
#ifndef ELEVADOR_H
#define ELEVADOR_H

typedef struct elevador
{
    int num_elev;
    char status;
    no *lista_demandas;
    int tempo_corrido;
    int andar_atual;
    int andares_max;
    int qtd_andares_percorridos;
    int tempo_deslocamento;
} elevador;

typedef struct no_elevador //aqui eh a lista de elevadores, assim como a struct de demandas tem um nó que serve pra ser a lista de demandas
{
    elevador e;
    struct no_elevador *ant;
    struct no_elevador *prox;
} no_elevador;

void criar_elevador();

void inserir_demanda();

void listar_demandas_elevador();

void preencher_dados_elevador();

void mostrar_elevadores();

void movimentar_elevador();

#endif

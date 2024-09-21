#include <stdio.h>
#include "demanda.h"
#ifndef ELEVADOR_H
#define ELEVADOR_H

typedef struct elevador
{
    int num_elev;
    char status;
    demanda *demandas;
    int tempo_corrido;
    int andar_atual;
    int andares_max;
} elevador;

void criar_elevador();

void inserir_demanda();

void preencher_dados_elevador();

#endif
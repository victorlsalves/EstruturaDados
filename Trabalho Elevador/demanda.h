#include <stdio.h>
#ifndef DEMANDA_H
#define DEMANDA_H

typedef struct demanda
{
    int tempo_recebido;
    int n_pessoa;
    char status;
    int andar_origem;
    int andar_destino;
} demanda;

typedef struct no //lista de demandas
{
    demanda d;
    struct no *ant;
    struct no *prox;
} no;

void inserir_comeco();

void inserir_final();

void alterar();

void remover();

void listar_demandas();

void ordenar_demandas();

void preencher_novas_demandas();

void remover_destino();

#endif

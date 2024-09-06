#include <stdio.h>
#ifndef DEMANDA_H
#define DEMANDA_H

typedef struct demanda
{
    int tempo;
    char pessoa[50];
    int andar_origem;
    int andar_destino;
} demanda;

typedef struct no
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

#endif
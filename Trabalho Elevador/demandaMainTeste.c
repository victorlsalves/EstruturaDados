#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demanda.h"

int main()
{
    no *l = NULL;
    demanda d1;
    demanda d2;
    demanda d3;
    demanda d4;
    
    d1.tempo = 1;
    strcpy(d1.pessoa, "Gus Fring");
    d1.andar_origem = 0;
    d1.andar_destino = 4;

    d2.tempo = 2;
    strcpy(d2.pessoa, "Walter White");
    d2.andar_origem = 2;
    d2.andar_destino = 8;

    d3.tempo = 3;
    strcpy(d3.pessoa, "Mossad");
    d3.andar_origem = 6;
    d3.andar_destino = 1;
    
    d4.tempo = 4;
    strcpy(d4.pessoa, "Jesse Pinkman");
    d4.andar_origem = 10;
    d4.andar_destino = 20;
    
    inserir_final(&l, d1);
    inserir_final(&l, d2);
    inserir_final(&l, d3);
    inserir_final(&l, d4);

    demanda d5;
    d5.tempo = 5;
    strcpy(d5.pessoa, "Miles Morales");
    d5.andar_origem = 44;
    d5.andar_destino = 40;
    alterar(&l, "Jesse Pinkman", d5);

    remover(&l, "Gus Fring");
    remover(&l, "Gus Frig");
    
    listar_demandas(&l);

    return 0;
}
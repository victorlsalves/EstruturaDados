#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demanda.h"
#include "elevador.h"
#include "utils.h"

int main()
{
    no_elevador *e = NULL; // lista onde ficam os elevadores
    no *l = NULL; // lista onde ficam as demandas
    char string_demandas[500];
    //strcpy(string_demandas, "AM_25 E1_04_S_6,9,8  E2_11_D_5,8,9,3,2,T E3_20_D_5,8,T,9 T5_P01_S_4_6 T9_P02_S_5_10 T10_P03_S_3_9 T10_P04_D_6_T T10_P05_S_8_15 T12_P01_D_6_4 T15_P06_D_9_2 T15_P07_S_2_13 T18_P08_D_8_T T21_P01_D_16_3 T21_P10_S_T_13 T21_P11_S_T_12 T23_P12_S_T_15 T28_P13_S_2_13");
    strcpy(string_demandas, "AM_16 E1_04_S_6,9,8 E2_11_D_5,8,9,3,2,T T5_P01_S_4_6 T9_P02_S_5_10 T10_P03_S_3_9 T10_P04_D_6_T T10_P05_S_8_15 T12_P01_D_6_4 T15_P06_D_9_2 T15_P07_S_2_13 T18_P08_D_8_T T21_P01_D_16_3 T21_P10_S_T_13 T21_P11_S_T_12 T23_P12_S_T_15 T28_P13_S_2_13");
    preencher_novas_demandas(&l, string_demandas);

    //listar_demandas(&l); // CARALHOOOO FUNCIONOU KKKKKKKKKKKKKKKKKKKKKKKK QUE FELICIDADE :)))))))))))))
    //ordenar_demandas(&l, 1); // insere em ordem crescente
    //ordenar_demandas(&l, 0); // insere em ordem decrescente
    //listar_demandas(&l);

    preencher_dados_elevador(&e, string_demandas);

    movimentar_elevador(e, l);

    return 0;
}

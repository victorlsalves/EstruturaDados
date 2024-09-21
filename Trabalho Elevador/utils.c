#include <stdio.h>
#include <stdlib.h>

int retornaDoisNumerosInteiro(char num1, char num2){
    int num;
    char numero[3];
    numero[0] = num1;
    numero[1] = num2;
    numero[3] = '\0';
    num = atoi(numero);
    return num;
}

int retornaUmNumeroInteiro(char num1){
    int num;
    char numero[2];
    numero[0] = num1;
    numero[1] = '\0';
    num = atoi(numero);
    return num;
}
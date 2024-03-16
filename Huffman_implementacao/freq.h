#ifndef freq_h
#define freq_h

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef unsigned char uchar;
typedef unsigned long long int ulli;

/*Função que cria um vetor de frequência, o calloc foi utlizado para inicializar o vetor com 0
sem a necessidade de um for para inicializar o vetor nem a necessidade da chamada da funão memset*/
ulli *criar_nova_freq();

//Função que conta a frequência de cada byte no arquivo
ulli *contar_frequencia(char *nome_arquivo);
ulli *contar_frequencia_from_file(FILE *arquivo);

#endif
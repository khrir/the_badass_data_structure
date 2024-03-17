#ifndef FREQ_H
#define FREQ_H

#include "../util/util.h"

/*
Cria um vetor de frequencia de 256 posições e inicializa todas as posições com 0

*/
int *criar_freq();

/*
Conta a frequencia de cada byte em um arquivo e retorna um vetor de frequencia

@param nome_arquivo: nome do arquivo a ser lido

*/
int *contar_freq(char *nome_arquivo);

#endif
#ifndef FREQ_H
#define FREQ_H

#include "../util/util.h"

// cria um vetor zerado de 256 posições
int *criar_freq();

// conta a frequência de cada caractere no arquivo
int *contar_freq(char *nome_arquivo);
int *contar_freq_from_file(FILE *arquivo);

#endif
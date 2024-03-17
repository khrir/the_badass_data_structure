#ifndef FREQ_H
#define FREQ_H

#include "../util/util.h"

// cria um vetor zerado de 256 posições
ulli *criar_freq();

// conta a frequência de cada caractere no arquivo
ulli *contar_freq(char *nome_arquivo);
ulli *contar_freq_from_file(FILE *arquivo);

void print_freq(ulli *freq);

#endif
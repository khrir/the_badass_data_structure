#ifndef FREQ_H
#define FREQ_H
#define MAX_SIZE 256

#include "../util/util.h"

/*
ADICIONAR NOVO COMENTARIO AQUI
*/
ulli *create_frequency_table();

/*
Conta a frequencia de cada byte em um arquivo e retorna um vetor de frequencia

@param nome_arquivo: nome do arquivo a ser lido

*/
void fill_frequency_table(ulli *frequencyTable, char *fileName);

#endif
#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "../util/util.h"
#include "../huff/huff.h"
#include "../fila_prio/fila_prio.h"

// lê o cabeçalho do arquivo comprimido e armazena o tamanho do lixo e da árvore
void ler_cabecalho(FILE *arq_comprimido, uchar *cabecalho, int *tmn_lixo, ulli *tmn_arvore);

//escreve os bytes descomprimidos no arquivo de saída
void escr_bytes_descomp(FILE *arq_comprimido, Node_prio *arvore, int tmn_lixo, FILE *arq_descomprimido);

//junta todas as funções de descompressão para descoprimir o arquivo
void descomprimir(char *arq_comprmido);

#endif
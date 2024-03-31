#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "../util/util.h"
#include "../huff/huff.h"
#include "../fila_prio/fila_prio.h"

/*
lê o cabeçalho do arquivo comprimido

@param arq_comprimido: arquivo comprimido
@param cabecalho: vetor de 2 bytes
@param tmn_lixo: tamanho do lixo
@param tmn_arvore: tamanho da árvore de huffman

*/
void ler_cabecalho(FILE *arq_comprimido, uchar *cabecalho, int *tmn_lixo, ulli *tmn_arvore);

/*
escreve os bytes descomprimidos no arquivo descomprimido

@param arq_comprimido: arquivo comprimido
@param arvore: árvore de huffman
@param tmn_lixo: tamanho do lixo
@param arq_descomprimido: arquivo descomprimido 

*/

void escr_bytes_descomp(FILE *arq_comprimido, Node_prio *arvore, int tmn_lixo, FILE *arq_descomprimido);

/*
Junta todas as funções de descompressão para descoprimir o arquivo, lê o arquivo comprimido bit a bit 
e usa a arvore de huffman para decodificar os bytes. A função ignora os bits de lixo no final do arquivo

@param arq_comprmido: nome do arquivo comprimido

*/
void descomprimir(char *arq_comprmido);

#endif
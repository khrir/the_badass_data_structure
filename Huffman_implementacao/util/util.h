#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
// #include <windows.h>

typedef unsigned char uchar;
typedef unsigned long long int ulli;

// retorna o tamanho do arquivo
int tmn_arquivo(char *nome_arquivo);

// retorna uma string digitada pelo usuario
char *input();

// agrupa os bits em bytes e salva no arquivo
void agrupar_em_bytes_e_salvar(char *nome_arquivo);

// limpa a tela do terminal
void limpar_tela();

// imprime uma arte no programa
void print_art1();

// imprime uma arte no programa
void print_art2();

#endif
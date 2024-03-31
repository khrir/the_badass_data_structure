#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef unsigned char uchar;
typedef unsigned long long int ulli;

/*
Retorna o tamanho do arquivo em bytes utliando a função fseek e ftell movendo o ponteiro até o final do arquivo
e retornando a posição do ponteiro que é o tamanho do arquivo

@param nome_arquivo: nome do arquivo a ser lido

*/
int tmn_arquivo(char *nome_arquivo);

/*
Retorna uma string com o nome do arquivo digitado pelo usuario

*/
char *input();

/*
Agrupa os bits em bytes e salva em um arquivo os bits que nao forma um byte completo
sao completados com zeros que serao indicado no cabeçalho do arquivo como lixo

@param nome_arquivo: nome do arquivo a ser lido

*/
void agrupar_em_bytes_e_salvar(char *nome_arquivo);

/*
Limpa a tela do terminal usanco uma sequencia de escape ANSI

*/
void limpar_tela();

/*
Imprime uma arte no terminal

*/
void print_art1();

/*
Imprime uma arte no terminal

*/
void print_art2();

#endif
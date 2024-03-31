#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef unsigned char uchar;
typedef unsigned long long int ulli;

typedef struct node {
    uchar byte;
    int frequencia;
    struct node *left, *right, *next;
} Node;

typedef struct list {
    Node *head;
    ulli current_size;
} List;

#include "../util/util.h"
#include "../code/code.h"
#include "../huff/huff.h"
#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"

/*
Junta as funções de compressão em uma só, para ser chamada no main

@param arq_comprimido: nome arquivo para ser comprimido

*/
void comprimir(char *nome_arquivo);

#endif

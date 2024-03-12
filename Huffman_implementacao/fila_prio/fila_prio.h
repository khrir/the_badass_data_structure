#ifndef FILA_PRIO_H
#define FILA_PRIO_H

#include "../util/util.h"

typedef struct Node_prio{
    int frequencia;
    uchar byte;
    struct Node_prio *next;
    struct Node_prio *left;
    struct Node_prio *right;
}Node_prio;

typedef struct Fila_prio{
    struct Node_prio *head;
}Fila_prio;

//cria uma fila de prioridade
Fila_prio *criar_fila();

//enfileira um byte com sua frequencia
void enfileirar(Fila_prio *fila, uchar byte, int frequencia);

//enfileira um no de arvore de huffman com os bytes e frequencia e os filhos
void enfila_huff(Fila_prio *fila, Node_prio *node);

//desenfileira um no da fila de prioridade
Node_prio *desenfileirar(Fila_prio *fila);

void imprimir_fila(Fila_prio *fila);

void free_fila(Fila_prio *fila);

#endif

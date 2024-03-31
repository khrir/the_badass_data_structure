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
    ulli current_size;
}Fila_prio;

/*
Cria uma fila de prioridade aloca memoria para a fila e inicializa a fila apontando para NULL

*/
Fila_prio *criar_fila();

/*
Enfileira um byte e sua frequencia na fila de prioridade

@param fila: fila de prioridade
@param byte: byte a ser enfileirado
@param frequencia: frequencia do byte a ser enfileirado

*/
void enfileirar(Fila_prio *list, ulli *frequencyTable);

//ADICIONAR COMENTARIOOOOOOO

void adiciona_ordenado(Fila_prio *list, Node_prio *node);

/*
Enfileira um no na fila de prioridade como um no de arvore de huffman

@param fila: fila de prioridade
@param node: no a ser enfileirado

*/
void enfila_huff(Fila_prio *fila, Node_prio *node);

/*
Desenfileira um no da fila de prioridade

@param fila: fila de prioridade

*/
Node_prio *desenfileirar(Fila_prio *list);

/*
Libera a memoria alocada para a fila de prioridade

@param fila: fila de prioridade

*/
void free_fila(Fila_prio *fila);

#endif

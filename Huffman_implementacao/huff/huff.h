#ifndef HUFF_H
#define HUFF_H

#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"
#include "../util/util.h"

// Função que cria a árvore de Huffman
void criar_huff_tree(Fila_prio *fila);

// Função que imprime a árvore de Huffman
void printar_huff_tree(Node_prio *node);



#endif


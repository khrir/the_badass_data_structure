#ifndef HUFF_H
#define HUFF_H

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct node_huff node_huff;
struct node_huff{
    uchar byte;
    ulli freq;
    node_huff *left;
    node_huff *right;
};

// cria novo nó da árvore de huffman
node_huff *new_node_huff(uchar byte, ulli freq, node_huff *left, node_huff *right);

// constroi a árvore de huffman
node_huff *constr_huff_tree(heap *hp);

// printa a árvore de huffman
void print_pre_order(node_huff *root);


#endif
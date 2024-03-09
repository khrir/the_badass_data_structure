#ifndef HUFF_H
#define HUFF_H

#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"
#include "../util/util.h"

typedef struct huff_dict{
    uchar mapa[256][16];
    int path_bits[256];
    int tmn[256];
    int freq[256];
}huff_dict;

// Função que cria a árvore de Huffman
void criar_huff_tree(Fila_prio *fila);

// Função que encontra as folhas da árvore de Huffman
int encontrar_folhas(Node_prio *node);

// Função que encontra a altura da árvore de Huffman
void altura_huff_tree(Node_prio *node, int *altura);

// Função que salva a árvore de Huffman em um arquivo
void salvar_huff_file(Node_prio *node, char *nome_arquivo);

// Função que cria um nó da árvore de Huffman
Node_prio *novo_huff_node(uchar byte, int frequencia, Node_prio *left, Node_prio *right);

// Função que constrói a árvore de Huffman a partir de um arquivo
Node_prio *contruir_huff_from_file(FILE *arquivo, Node_prio *huff_tree, int *altura_tree);

// Função que libera a memória alocada para a árvore de Huffman
void free_huff_tree(Node_prio *node);

// Função que cria um dicionário de Huffman
huff_dict *criar_huff_dict();












#endif


#ifndef HUFF_H
#define HUFF_H

#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"
#include "../util/util.h"

 
/*
Desenfileira um no da fila de prioridade e cria um novo no
com a soma das frequencias dos dois primeiros nos da fila de prioridade

@param fila: fila de prioridade

*/
void criar_huff_tree(Fila_prio *fila);


/*
Função que encontra as folhas da árvore de Huffman verificando se o nó aponta para NULL nos dois filhos

@param node: nó da árvore de Huffman

*/
int encontrar_folhas(Node_prio *node);

/*
Função recusiva que percorre a árvore de Huffman salva o tamanho da arvore utlizando ponteiro

@param node: nó da árvore de Huffman
@param tmn: ponteiro para o tamanho da árvore

*/
void tamanho_huff_tree(Node_prio *node, ulli *tmn);

/*
Salva a árvore de Huffman em um arquivo levando em considerao o caractere de escape

@param node: nó da árvore de Huffman
@param nome_arquivo: nome do arquivo que vai receber a arvore

*/
void salvar_huff_file(Node_prio *node, char *nome_arquivo);

/*
Cria um novo nó da árvore de Huffman reutilizando a estrutura de nó da fila de prioridade que continha
as variaveis left e right em seu estado latente

@param byte: byte a ser armazenado no nó
@param frequencia: frequencia do byte
@param left: ponteiro para o filho esquerdo
@param right: ponteiro para o filho direito

*/
Node_prio *novo_huff_node(uchar byte, int frequencia, Node_prio *left, Node_prio *right);

/*
Constroi a árvore de Huffman a partir de um arquivo comprimido que contem a arvore de Huffman

@param arquivo: arquivo que contem a arvore de Huffman
@param huff_tree: ponteiro para a raiz da árvore de Huffman
@param tmn_arvore: tamanho da arvore de Huffman

*/
Node_prio *construir_huff_from_file(FILE *arquivo, Node_prio *huff_tree, ulli *tmn_arvore);

/*
Libera a memoria alocada para a árvore de Huffman

@param node: nó da árvore de Huffman

*/
void free_huff_tree(Node_prio *node);

#endif


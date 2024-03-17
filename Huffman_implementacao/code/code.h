#ifndef CODE_H
#define CODE_H

#include "../util/util.h"
#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"
#include "../huff/huff.h"

typedef struct Node_lista{
    uchar item;
    struct Node_lista *next;
}Node_lista;

// Cria um novo Node_lista
Node_lista *novo_Node_lista(Node_lista *node, int item);

// Remove um Node_lista
Node_lista *remove_Node_lista(Node_lista *node);

// Faz uma lista de binários e escreve no arquivo
void escrv_lista_bin(FILE *arquivo, Node_lista *node);

// Escreve o caminho codificado que é feito na funcaçao escrv_lista_bin no arquivo
void gerar_caminho(FILE *arq_code, Node_prio *node, int byte, Node_lista *lista_bin);

// Escreve os bytes codificados no arquivo
void escrv_bytes_cod(char *nome_arquivo, Node_prio *fila);

// Calcula o lixo que será escrito no arquivo
int calc_lixo(char *nome_arquivo);

// Escreve o cabeçalho contendo o lixo e a altura da árvore 
void escrever_cabecalho(int tmn_lixo, int altura_arvore, char *nome_arquivo);

// salva as informações de cabeçalho, arvore e os dados do aqruivo comprimido
void salvar_no_arquivo(char *nome_arquivo, int tamanho_arvore, Fila_prio *fila);


#endif
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

/*
Cria um novo no de uma lista

@param node: Node_lista
@param item: item do Node_lista

*/
Node_lista *novo_Node_lista(Node_lista *node, int item);

/*
Remove um no de uma lista

@param node: Node_lista

*/
Node_lista *remove_Node_lista(Node_lista *node);

/*
Escreve a lista de binarios no arquivo

@param arquivo: arquivo
@param node: no da lista

*/
void escrv_lista_bin(FILE *arquivo, Node_lista *node);

/*
Cria o caminho codificado que é feito na funcaçao escrv_lista_bin no arquivo

@param arq_code: arquivo que vai receber o caminho codificado
@param node: no da arvore
@param byte: byte que vai ser codificado
@param lista_bin: lista de binarios

*/
void gerar_caminho(FILE *arq_code, Node_prio *node, int byte, Node_lista *lista_bin);

/*
Escreve os bytes codificados no arquivo

@param nome_arquivo: nome do arquivo que vai ser codificado
@param fila: fila de prioridade

*/
void escrv_bits_cod(char *nome_arquivo, Node_prio *fila);

/*
Calcula o lixo que vai ser adicionado no arquivo

@param nome_arquivo: nome do arquivo que vai ser comprimido

*/
int calc_lixo(char *nome_arquivo);

/*
Escreve o cabeçalho no arquivo

@param tmn_lixo: tamanho do lixo
@param tmn_arvore: tamanho da arvore
@param nome_arquivo: nome do arquivo final

*/
void escrever_cabecalho(int tmn_lixo, int tmn_arvore, char *nome_arquivo);

/*
Junta todas as funções de codificação para codificar e salvar o arquivo

@param nome_arquivo: nome do arquivo que vai ser comprimido
@param tmn_arvore: tamanho da arvore
@param fila: fila de prioridade

*/
void salvar_no_arquivo(char *nome_arquivo, int tmn_arvore, Fila_prio *fila);


#endif
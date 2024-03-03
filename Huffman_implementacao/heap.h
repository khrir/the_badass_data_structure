#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HP_SIZE 256

typedef unsigned char uchar;
typedef unsigned long long int ulli;


//Estrutura que representa um nó da heap com prioridade
typedef struct prio_hp_node{
    void *item;
    ulli prioridade;
}prio_hp_node;

//Estrutura padrão de uma heap com a variavel max_size que representa o tamanho maximo da heap
// para que não seja necessário alocar mais memória do que o necessário
typedef struct heap{
    prio_hp_node *arr[MAX_HP_SIZE];
    ulli size;
    ulli max_size;
}heap;

//Função que troca dois nós da heap
void swap(prio_hp_node **a, prio_hp_node **b);

//Função que cria um novo nó da heap
prio_hp_node *new_node(void *item, ulli prioridade );

heap *criar_heap();

/* A funcao heapify é responsável por manter propriedade de heap apos a remocao ou insercao de um elemento
em uma min heap, para qualquer nó i, o valor desse nó é maior ou igual ao valor de seu pai e menor ou igual
aos valores de seus filhos. Em outras palavras, o nó pai é sempre menor ou igual aos seus nós filhos.
O nó na raiz, portanto, é o menor nó.*/
void min_heapify(heap *hp, ulli i);

void push_heap(heap *hp, void *item, ulli prioridade);

/*A função copiar_node cria e retorna uma cópia de um nó existente.
vai ser util na funcao pop_heap, onde queremos retornar o nó removido
sem alterar a estrutura original da heap.*/
prio_hp_node *copiar_node(prio_hp_node *node);

/*A função pop_heap remove o nó com menor prioridade da heap e retorna o nó removido
a função min_heapify é chamada para manter a propriedade de heap após a remoção do nó.
o nó removido é retornado para que possa ser utilizado na construção da árvore de Huffman.*/
prio_hp_node *pop_heap(heap *hp);

//Função que imprime a heap
void print_heap(heap *hp);

//Função que libera a memória alocada para a heap
void free_heap(heap *hp);

//Verifica se atende as propriedades de heap
int check_heap(heap *hp);   
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
    int prioridade;
}prio_hp_node;

//Estrutura padrão de uma heap com a variavel max_size que representa o tamanho maximo da heap
// para que não seja necessário alocar mais memória do que o necessário
typedef struct heap{
    prio_hp_node *arr[MAX_HP_SIZE];
    int size;
    int max_size;
}heap;

void swap(prio_hp_node **a, prio_hp_node **b){
    prio_hp_node *temp = *a;
    *a = *b;
    *b = temp;
}

prio_hp_node *new_node(void *item, int prioridade ){
    prio_hp_node *new_node = (prio_hp_node*)malloc(sizeof(prio_hp_node));
    new_node->item = item;
    new_node->prioridade = prioridade;
    return new_node;
}

heap *criar_heap(){
    heap *new_heap = (heap*)malloc(sizeof(heap));
    new_heap->size = 0;
    new_heap->max_size = MAX_HP_SIZE;
    for(int i = 0; i < MAX_HP_SIZE; i++) new_heap->arr[i] = NULL;
    return new_heap;
}

/* A funcao heapify é responsável por manter propriedade de heap apos a remocao ou insercao de um elemento
em uma min heap, para qualquer nó i, o valor desse nó é maior ou igual ao valor de seu pai e menor ou igual
aos valores de seus filhos. Em outras palavras, o nó pai é sempre menor ou igual aos seus nós filhos.
O nó na raiz, portanto, é o menor nó.*/
void min_heapify(heap *hp, int i){
    int menor;
    int left = i << 1;
    int right = (i << 1) + 1;

    if(left <= hp->size  && hp->arr[left]->prioridade < hp->arr[i]->prioridade) menor = left;
    else menor = i;
    if(right <= hp->size && hp->arr[right]->prioridade < hp->arr[menor]->prioridade) menor = right;
    if(hp->arr[i] != hp->arr[menor]){
        swap(&hp->arr[i],&hp->arr[menor]);
        min_heapify(hp,menor);
    }
}

void push_heap(heap *hp, void *item, int prioridade){
    prio_hp_node *node = new_node(item, prioridade);
    hp->size++;
    hp->arr[hp->size] = node;
    min_heapify(hp, hp->size);
}

/*A função copiar_node cria e retorna uma cópia de um nó existente.
vai ser util na funcao pop_heap, onde queremos retornar o nó removido
sem alterar a estrutura original da heap.*/
prio_hp_node *copiar_node(prio_hp_node *node){
    prio_hp_node *copiar_node = new_node(node->item, node->prioridade);
    return copiar_node;
}


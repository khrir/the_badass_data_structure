#include "heap.h"


void swap(prio_hp_node **a, prio_hp_node **b){
    prio_hp_node *temp = *a;
    *a = *b;
    *b = temp;
}

prio_hp_node *new_node(void *item, ulli prioridade ){
    prio_hp_node *new_node = (prio_hp_node*)malloc(sizeof(prio_hp_node));
    new_node->item = item;
    new_node->prioridade = prioridade;
    return new_node;
}

heap *criar_heap(){
    heap *new_heap = (heap*)malloc(sizeof(heap));
    new_heap->size = 0;
    new_heap->max_size = MAX_HP_SIZE;
    for(ulli i = 0; i < MAX_HP_SIZE; i++) new_heap->arr[i] = NULL;
    return new_heap;
}

void min_heapify(heap *hp, ulli i){
    ulli menor;
    ulli left = i << 1;
    ulli right = (i << 1) + 1;

    if(left <= hp->size  && hp->arr[left]->prioridade < hp->arr[i]->prioridade) menor = left;
    else menor = i;
    if(right <= hp->size && hp->arr[right]->prioridade < hp->arr[menor]->prioridade) menor = right;
    if(hp->arr[i] != hp->arr[menor]){
        swap(&hp->arr[i],&hp->arr[menor]);
        min_heapify(hp,menor);
    }
}

void push_heap(heap *hp, void *item, ulli prioridade){
    prio_hp_node *node = new_node(item, prioridade);
    hp->size++;
    hp->arr[hp->size] = node;
    min_heapify(hp, hp->size);
}

prio_hp_node *copiar_node(prio_hp_node *node){
    prio_hp_node *copiar_node = new_node(node->item, node->prioridade);
    return copiar_node;
}

prio_hp_node *pop_heap(heap *hp){
    if(hp->size == 0) return NULL;
    prio_hp_node *node = copiar_node(hp->arr[1]);
    if(hp->size > 1) swap(&hp->arr[1],&hp->arr[hp->size]);
    hp->size--;
    min_heapify(hp,1);
    return node;
}


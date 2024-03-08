#ifndef _LISTA_H
#define _LISTA_H

#include "../util/util.h"

typedef struct Node_lista{
    int item; 
    struct node *next;
}Node_lista;
    
// cria um nó da lista
Node_lista *criar_node_lista(Node_lista *node, int item);

// remove um nó da lista
void rmv_node_lista(Node_lista *node);

// da free na lista
void free_lista(Node_lista *node);

#endif
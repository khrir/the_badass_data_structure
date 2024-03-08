#include "lista.h"

Node_lista *criar_node_lista(Node_lista *node, int item){
    Node_lista *new_node = (Node_lista*)malloc(sizeof(Node_lista));
    new_node->item = item;
    new_node->next = node;
    return new_node;
}

void rmv_node_lista(Node_lista *node){
    Node_lista *aux = node;
    node = node->next;
    free(aux);
}

void free_lista(Node_lista *node){
    Node_lista *aux = node;
    while(aux != NULL){
        node = node->next;
        free(aux);
        aux = node;
    }
}
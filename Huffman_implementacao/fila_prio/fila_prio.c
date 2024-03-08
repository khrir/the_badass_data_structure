#include "fila_prio.h"

Fila_prio *criar_fila(){
    Fila_prio *nova_fp = (Fila_prio*)malloc(sizeof(Fila_prio));
    nova_fp->head = NULL;
    return nova_fp; 
}

void enfileirar(Fila_prio *fila, uchar byte, int frequencia){
    Node_prio *new_node = (Node_prio*)malloc(sizeof(Node_prio));
    new_node->byte = byte;
    new_node->frequencia = frequencia;
    new_node->left = NULL;
    new_node->right = NULL;
    if(fila->head == NULL || frequencia < fila->head->frequencia){
        new_node->next = fila->head;
        fila->head = new_node;
    }
    else{
        Node_prio *current = fila->head;
        while(current->next != NULL && current->next->frequencia <= frequencia) current = current->next;
        new_node->next = current->next;
        current->next = new_node;
    }
}

void enfila_huff(Fila_prio *fila, Node_prio *node){
    if(fila->head == NULL || node->frequencia <= fila->head->frequencia){
        node->next = fila->head;
        fila->head = node;
    }
    else{
        Node_prio *current = fila->head;
        while(current->next != NULL && current->next->frequencia < node->frequencia) current = current->next;
        node->next = current->next;
        current->next = node;
    }
}

Node_prio *desenfileirar(Fila_prio *fila){
    if(fila->head == NULL) return NULL;
    Node_prio *aux = fila->head;
    fila->head = fila->head->next;
    aux->next = NULL;
    return aux;
}
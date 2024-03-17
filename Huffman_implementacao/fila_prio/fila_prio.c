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
    
    if(fila->head == NULL || frequencia < fila->head->frequencia || (frequencia == fila->head->frequencia && byte > fila->head->byte)){
        new_node->next = fila->head;
        fila->head = new_node;
    }
    else{
        Node_prio *current = fila->head;
        while(current->next != NULL && (current->next->frequencia < frequencia || (current->next->frequencia == frequencia && current->next->byte > byte))) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void enfila_huff(Fila_prio *fila, Node_prio *node){
    if(fila->head == NULL || node->frequencia < fila->head->frequencia || (node->frequencia == fila->head->frequencia && node->byte > fila->head->byte)){
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

void imprimir_fila(Fila_prio *fila){
    Node_prio *current = fila->head;
    while(current != NULL){
        printf("Byte: %d [%c], Frequencia: %d\n", current->byte, current->byte, current->frequencia);
        current = current->next;
    }
}

void free_fila(Fila_prio *fila){
    Node_prio *current = fila->head;
    while(current != NULL){
        Node_prio *aux = current;
        current = current->next;
        free(aux);
    }
    free(fila);
}
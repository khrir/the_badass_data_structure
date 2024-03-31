#include "fila_prio.h"

/**
 * @brief Create a new priority queue
 * 
 * @return Fila_prio* 
 */
Fila_prio *criar_fila(){
    Fila_prio *nova_fp = (Fila_prio*)malloc(sizeof(Fila_prio));
    nova_fp->head = NULL;
    nova_fp->current_size=0;
    return nova_fp; 
}

/**
 * @brief Insert a new node in the priority queue
 * 
 * @param fila 
 * @param byte 
 * @param frequencia 
 * @return void
 */
void enfileirar(Fila_prio *list, ulli *frequencyTable) {
    for(int i = 0; i < MAX_SIZE; i++){
        if(frequencyTable[i] != 0){
            Node_prio *node = (Node_prio *)malloc(sizeof(Node_prio));
            node->byte = (uchar)i;
            node->frequencia = frequencyTable[i];
            node->left = NULL;
            node->right = NULL;
            node->next = NULL;

            adiciona_ordenado(list, node);
        }
    }
}

/**
 * @brief Insert a new node in queue
 * 
 * @param fila 
 * @param node 
 * @return void
 */

void adiciona_ordenado(Fila_prio *list, Node_prio *node){
    Node_prio *current = list->head;
    Node_prio *previous = NULL;

    if(current == NULL){
        list->head = node;
        node->next = NULL;
    } else if (node->frequencia < current->frequencia){
        node->next = current;
        list->head = node;
    } else {
        while(current != NULL && node->frequencia >= current->frequencia){
            previous = current;
            current = current->next;
        }
        if(previous != NULL) {
            previous->next = node;
        }
        node->next = current;
    }

    list->current_size++;
}

/**
 * @brief Insert a new node in the huffman priority queue
 * 
 * @param fila 
 * @param node 
 * @return void
 */
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

/**
 * @brief Remove the first node from the priority queue
 * 
 * @param fila 
 * @return Node_prio* 
 */

Node_prio *desenfileirar(Fila_prio *list){
    Node_prio *aux = NULL;

    if(list->current_size > 0){
        aux = list->head;
        list->head = list->head->next;
        aux->next = NULL;
        list->current_size--;
    }

    return aux;
}

/**
 * @brief Print the priority queue
 * 
 * @param fila 
 * @return void
 */
void imprimir_fila(Fila_prio *fila){
    Node_prio *current = fila->head;
    while(current != NULL){
        printf("Byte: %c, Frequencia: %d\n", current->byte, current->frequencia);
        current = current->next;
    }
}

/**
 * @brief Free the priority queue
 * 
 * @param fila 
 * @return void
 */
void free_fila(Fila_prio *fila){
    Node_prio *current = fila->head;
    while(current != NULL){
        Node_prio *aux = current;
        current = current->next;
        free(aux);
    }
    free(fila);
}
#include "huff.h"

void criar_huff_tree(Fila_prio *fila){
    while(fila->head->next != NULL){
        Node_prio *left = desenfileirar(fila);
        Node_prio *right = desenfileirar(fila);
        Node_prio *new_node = (Node_prio*)malloc(sizeof(Node_prio));
        new_node->byte = '*';
        new_node->frequencia = left->frequencia + right->frequencia;
        new_node->left = left;
        new_node->right = right;
        enfila_huff(fila, new_node);
    }
    puts("Arvore de huffman criada com sucesso!");
}

void printar_huff_tree(Node_prio *node){
    if(node != NULL){
        if(node->byte != '*'){
            print_byte(node->byte);
            printf(" %d\n", node->frequencia);
        }else{
            printf("*\n", node->frequencia);
        }
        printar_huff_tree(node->left);
        printar_huff_tree(node->right);
    }
}

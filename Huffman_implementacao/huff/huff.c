#include "huff.h"

Node_prio *novo_huff_node(uchar byte, int frequencia, Node_prio *left, Node_prio *right){
    Node_prio *new_node = (Node_prio*)malloc(sizeof(Node_prio));
    new_node->byte = byte;
    new_node->frequencia = frequencia;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

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
}

void tamanho_huff_tree(Node_prio *node, int *tmn){
    if(node){
        *tmn += 1;
        tamanho_huff_tree(node->left, tmn);
        tamanho_huff_tree(node->right, tmn);
    }
}

int encontrar_folhas(Node_prio *node){
    return(node->left == NULL && node->right == NULL);
}
// "a" para append, significa que o arquivo será aberto para escrita, mas o conteúdo atual não será apagado
// ou seja o conteúdo será adicionado ao final do arquivo
void salvar_huff_file(Node_prio *node, char *nome_arquivo){
    if(node){
        FILE *arquivo = fopen(nome_arquivo, "a"); 
        if((node->byte == '*' || node->byte == '\\') && encontrar_folhas(node)){
            fprintf(arquivo, "\\%c", node->byte);
        }
        else fprintf(arquivo, "%c", node->byte);
        fclose(arquivo);
        salvar_huff_file(node->left, nome_arquivo); 
        salvar_huff_file(node->right, nome_arquivo);       
    }
}

Node_prio *contruir_huff_from_file(FILE *arquivo, Node_prio *huff_tree, int *altura_tree){
    printf("Current tree height: %d\n", *altura_tree);
    if(*altura_tree > 0){
        uchar byte = fgetc(arquivo);
        printf("Read byte: %c\n", byte);
        *altura_tree -= 1;

        if(byte == '*'){
            puts("Byte is '*', creating internal node");
            huff_tree = novo_huff_node('*', 0, NULL, NULL);
            huff_tree->left = contruir_huff_from_file(arquivo, huff_tree->left, altura_tree);
            huff_tree->right = contruir_huff_from_file(arquivo, huff_tree->right, altura_tree);
        }
        else{
            puts("Byte is not '*', creating leaf node");
            if(byte == '\\'){
                puts("Byte is '\\', reading next byte");
                byte = fgetc(arquivo);
                printf("Next byte: %c\n", byte);
                *altura_tree -= 1;
            }
            huff_tree = novo_huff_node(byte, 0, NULL, NULL);
        }
    }
    puts("Finished building tree at this level");
    return huff_tree;
}

void free_huff_tree(Node_prio *node){
    if(node){
        free_huff_tree(node->left);
        free_huff_tree(node->right);
        free(node);
    }
}

 
void pre_order(Node_prio *node, char *nome_arquivo){
    if(node){
        FILE *arquivo = fopen(nome_arquivo, "a");
        fprintf(arquivo, "%c", node->byte);
        pre_order(node->left, nome_arquivo);
        pre_order(node->right, nome_arquivo);
    }
}   
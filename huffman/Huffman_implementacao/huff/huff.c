#include "huff.h"

/**
 * @brief Create a new Huffman node
 * 
 * @param byte 
 * @param frequencia 
 * @param left 
 * @param right 
 * @return Node_prio* 
 */
Node_prio *novo_huff_node(uchar byte, int frequencia, Node_prio *left, Node_prio *right){
    Node_prio *new_node = (Node_prio*)malloc(sizeof(Node_prio));
    new_node->byte = byte;
    new_node->frequencia = frequencia;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

/**
 * @brief Create the Huffman Tree
 * 
 * @param fila
 * @return Fila_prio* 
 */
Node_prio *criar_huff_tree(Fila_prio *fila){
    while(fila->head->next != NULL){
        Node_prio *left = desenfileirar(fila);
        Node_prio *right = desenfileirar(fila);
        Node_prio *new_node = (Node_prio*)malloc(sizeof(Node_prio));
        new_node->byte = '*';
        new_node->frequencia = left->frequencia + right->frequencia;
        new_node->left = left;
        new_node->right = right;
        adiciona_ordenado(fila, new_node);
    }
    return fila->head;
}

/**
 * @brief Count the size of the Huffman Tree
 * 
 * @param node
 * @param tmn
 * @return void
 */
void tamanho_huff_tree(Node_prio *node, ulli *tmn){
    if(node){
        *tmn += 1;
        tamanho_huff_tree(node->left, tmn);
        tamanho_huff_tree(node->right, tmn);
    }
}

/**
 * @brief Seach for the leaves of the Huffman Tree
 * 
 * @param node
 * @return int
 */
int encontrar_folhas(Node_prio *node){
    return(node->left == NULL && node->right == NULL);
}

/**
 * @brief Save the Huffman Tree in a file
 * 
 * @param node 
 * @param nome_arquivo 
 * @return void
 */
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

/**
 * @brief Build the Huffman Tree from a file
 * 
 * @param arquivo 
 * @param huff_tree 
 * @param tmn_arvore 
 * @return Node_prio* 
 */
Node_prio *construir_huff_from_file(FILE *arquivo, Node_prio *huff_tree, ulli *tmn_arvore){
    if(*tmn_arvore > 0){
        uchar byte = fgetc(arquivo);
        *tmn_arvore -= 1;

        if(byte == '*'){
            huff_tree = novo_huff_node('*', 0, NULL, NULL);
            huff_tree->left = construir_huff_from_file(arquivo, huff_tree->left, tmn_arvore);
            huff_tree->right = construir_huff_from_file(arquivo, huff_tree->right, tmn_arvore);
        }
        else{
            if(byte == '\\'){
                byte = fgetc(arquivo);
                *tmn_arvore -= 1;
            }
            huff_tree = novo_huff_node(byte, 0, NULL, NULL);
        }
    }
    return huff_tree;
}

/**
 * @brief Free the Huffman Tree
 * 
 * @param node 
 * @return void
 */
void free_huff_tree(Node_prio *node){
    if(node){
        free_huff_tree(node->left);
        free_huff_tree(node->right);
        free(node);
    }
}

/**
 * @brief Write the tree in pre-order
 * 
 * @param node 
 * @param nome_arquivo 
 * @return void
 */
void pre_order(Node_prio *node, char *nome_arquivo){
    if(node){
        FILE *arquivo = fopen(nome_arquivo, "a");
        fprintf(arquivo, "%c", node->byte);
        pre_order(node->left, nome_arquivo);
        pre_order(node->right, nome_arquivo);
    }
}   
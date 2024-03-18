#include "code.h"

/**
 * @brief Create a new node
 * 
 * @param node 
 * @param item 
 * @return Node_lista* 
 */
Node_lista *novo_Node_lista(Node_lista *node, int item){
    Node_lista *new_node = (Node_lista*)malloc(sizeof(Node_lista));
    new_node->item = item;
    new_node->next = node;
    return new_node;
}

/**
 * @brief Remove a node from the list
 * 
 * @param node 
 * @return Node_lista* 
 */
Node_lista *remove_Node_lista(Node_lista *node){
    if (node == NULL) return NULL;
    Node_lista *next_node = node->next;
    free(node);
    return next_node;
}

/**
 * @brief Write the binary list in a file
 * 
 * @param arquivo 
 * @param node 
 * @return void
 */
void escrv_lista_bin(FILE *arquivo, Node_lista *node){
    if(node){
        escrv_lista_bin(arquivo, node->next);
        fprintf(arquivo, "%d", node->item);
    }
    return;
}

/**
 * @brief Create the way to the byte
 * 
 * @param arq_code 
 * @param node 
 * @param byte 
 * @param lista_bin 
 * @return void
 */
void gerar_caminho(FILE *arq_code, Node_prio *node, int byte, Node_lista *lista_bin){
    if(node){
        if(node->byte == byte){
            escrv_lista_bin(arq_code, lista_bin);
            return;
        }
        gerar_caminho(arq_code, node->left, byte, novo_Node_lista(lista_bin, 0));
        gerar_caminho(arq_code, node->right, byte, novo_Node_lista(lista_bin, 1));
    }
    else remove_Node_lista(lista_bin);
}

/**
 * @brief Write the tree in a file
 * 
 * @param nome_arquivo 
 * @param fila 
 * @return void
 */
void escrv_bits_cod(char *nome_arquivo, Node_prio *fila){
    FILE *arq_pai = fopen(nome_arquivo, "rb");
    FILE *arq_cod = fopen("bytes_code.txt", "wb");
    uchar byte_lido;
    size_t result;
    while((result = fread(&byte_lido, sizeof(uchar), 1, arq_pai)) > 0){
        gerar_caminho(arq_cod, fila, byte_lido, NULL);
    }
    fclose(arq_pai);
    fclose(arq_cod);
}

/**
 * @brief Calculate the trash size
 * 
 * @param nome_arquivo 
 * @return int
 */
int calc_lixo(char *nome_arquivo){
    FILE *arq = fopen(nome_arquivo, "rb");
    ulli bits = 0;
    while(fgetc(arq) != EOF) bits++;
    fclose(arq);
    int resto = bits % 8; 
    return (resto > 0) ? 8 - resto : 0;
}

/**
 * @brief Write the header of the file
 * 
 * @param tmn_lixo
 * @param tmn_arvore 
 * @param nome_arquivo 
 * @return void
 */
void escrever_cabecalho(int tmn_lixo, int tmn_arvore, char *nome_arquivo){
    uchar byte1, byte2;
    FILE *arquivo = fopen(nome_arquivo, "wb");
    byte1 = (tmn_lixo << 5) | (tmn_arvore >> 8);
    byte2 = tmn_arvore;
    fputc(byte1, arquivo);
    fputc(byte2, arquivo);
    fclose(arquivo);
}

/**
 * @brief Save the tree in a file
 * 
 * @param nome_arquivo 
 * @param tmn_arvore
 * @param fila 
 * @return void
 */
void salvar_no_arquivo(char *nome_arquivo, int tmn_arvore, Fila_prio *fila){
    
    FILE *arq_codificado = fopen("bytes_code.txt", "rb");
    int tmn_lixo = calc_lixo("bytes_code.txt");
    puts("Lixo calculado!");
    fclose(arq_codificado);

    char *nome_arq_final = (char*)malloc(50*sizeof(char));
    strcpy(nome_arq_final, nome_arquivo);
    strcat(nome_arq_final, ".sccp");

    FILE *arq_final = fopen(nome_arq_final, "wb");
    escrever_cabecalho(tmn_lixo, tmn_arvore, nome_arq_final);
    puts("Cabecalho escrito!");

    salvar_huff_file(fila->head, nome_arq_final);
    puts("Arvore salva no arquivo!");
    fclose(arq_final);

    FILE *arq_compac = fopen(nome_arq_final, "ab");

    FILE *arq_cod = fopen("caminho_bytes.txt", "rb");
    uchar byte;
    size_t result;
    while((result = fread(&byte, sizeof(uchar), 1, arq_cod)) > 0){
        fwrite(&byte, sizeof(uchar), 1, arq_compac);
    }

    fclose(arq_cod);
    fclose(arq_compac);
    free(nome_arq_final);
}
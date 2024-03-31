#include "compress.h"

/**
 * @brief Compress the file
 * 
 * @param nome_arquivo
 * @return void
 */

void comprimir(char *nome_arquivo){

    FILE *file = fopen(nome_arquivo, "rb");

    ulli *frequencyTable = create_frequency_table();
    fill_frequency_table(frequencyTable, nome_arquivo);

    Fila_prio *fila = criar_fila();

    for(int i = 0; i < 256; i++){
        if(frequencyTable[i] != 0)
            enfileirar(fila, (uchar)i, frequencyTable[i]);
    }

    Node_prio *root = criar_huff_tree(fila);
    ulli tamanho_arvore = 0;
    tamanho_huff_tree(fila->head, &tamanho_arvore);
    int colunas = calculate_altura(root)+1;
    uchar **dictionary = create_dictionary(colunas);
    

    /*escrv_bits_cod(nome_arquivo, fila->head);
    agrupar_em_bytes_e_salvar("caminho_bytes.txt");*/

    salvar_no_arquivo(nome_arquivo, tamanho_arvore, fila);
    free(frequencyTable);
    free(fila);
}
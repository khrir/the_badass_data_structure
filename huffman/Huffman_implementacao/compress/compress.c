#include "compress.h"

//AAAAAABBBBBCCCCDDDEEF

/**
 * @brief Compress the file
 * 
 * @param nome_arquivo
 * @return void
 */

void print_dictionary(uchar **dictionary) {
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        if(strlen((char *)dictionary[i]) > 0){
            printf("%c: %s\n", (uchar)i, dictionary[i]);
        }
    }
}

void comprimir(char *nome_arquivo){

    FILE *file = fopen(nome_arquivo, "rb");

    ulli *frequencyTable = create_frequency_table();
    fill_frequency_table(frequencyTable, nome_arquivo);

    Fila_prio *fila = criar_fila();
    enfileirar(fila,frequencyTable);

    Node_prio *root = criar_huff_tree(fila);
    ulli tamanho_arvore = 0;
    tamanho_huff_tree(fila->head, &tamanho_arvore);

    int colunas=calculate_altura(root)+1;
    uchar **dictionary = create_dictionary(colunas);
    fill_dictionary(root, dictionary, "", colunas);
    print_dictionary(dictionary);

    uchar *text=file_to_string(nome_arquivo);
    uchar *code=codifica(dictionary,text);
    printf("Codigo: %s\n", code);

    salvar_no_arquivo(nome_arquivo, tamanho_arvore, fila, code);

    /*escrv_bits_cod(nome_arquivo, fila->head);
    agrupar_em_bytes_e_salvar("caminho_bytes.txt");*/


    free(frequencyTable);
    free_dictionary(dictionary);
    free(fila);
}
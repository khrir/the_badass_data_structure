#include "compress.h"

/**
 * @brief Compress the file
 * 
 * @param nome_arquivo
 * @return void
 */
void comprimir(char *nome_arquivo){
    int *freq = contar_freq(nome_arquivo);
    Fila_prio *fila = criar_fila();
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0)
            enfileirar(fila, (uchar)i, freq[i]);
    }
    criar_huff_tree(fila);
    ulli tamanho_arvore = 0;
    tamanho_huff_tree(fila->head, &tamanho_arvore);
    escrv_bits_cod(nome_arquivo, fila->head);
    agrupar_em_bytes_e_salvar("caminho_bytes.txt");
    salvar_no_arquivo(nome_arquivo, tamanho_arvore, fila);
    free(freq);
    free(fila);
}
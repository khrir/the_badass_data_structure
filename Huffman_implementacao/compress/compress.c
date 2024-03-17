#include "compress.h"

int comprimir(char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if(!arquivo){
        perror("Arquivo não encontrado!");
        return 0;
    }
    fclose(arquivo);

    int *freq = contar_freq(nome_arquivo);
    Fila_prio *fila = criar_fila();
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0)
            enfileirar(fila, (uchar)i, freq[i]);
    }
    criar_huff_tree(fila);
    ulli tamanho_arvore = 0;
    tamanho_huff_tree(fila->head, &tamanho_arvore);
    escrv_bytes_cod(nome_arquivo, fila->head);
    agrupar_em_bytes_e_salvar("tmp/caminho_bytes.txt");
    salvar_no_arquivo(nome_arquivo, tamanho_arvore, fila);
    free(freq);
    free(fila);
    return 1;
}
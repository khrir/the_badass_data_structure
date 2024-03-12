#include "compress.h"

void comprimir(char *nome_arquivo){
    int tmn_arq_inic = tmn_arquivo(nome_arquivo);

    int *freq = criar_freq();
    freq = contar_freq(nome_arquivo);
    Fila_prio *fila = criar_fila();
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0)
            enfileirar(fila, i, freq[i]);
    }
    criar_huff_tree(fila);
    int tamanho_arvore = 0;
    tamanho_huff_tree(fila->head, &tamanho_arvore);
    escrv_bytes_cod(nome_arquivo, fila->head);
    agrupar_em_bytes_e_salvar("caminho_bytes.txt");

    //escrv_bytes_cod(nome_arquivo, fila); vai gerar o txt bytes_code.txt
    // preciso pegar depis esse txt e transformar em binario espaçado em bytes e aí sim salvar no arquivo
    salvar_no_arquivo(nome_arquivo, tamanho_arvore, fila);

    FILE *arquivo_compress = fopen("entradaimt.png.sccp", "r");
    int tmn_arq_final = tmn_arquivo("entradaimt.png.sccp");
    fclose(arquivo_compress);
    printf("Tamanho do arquivo original: %d bytes\n", tmn_arq_inic);
    printf("Tamanho do arquivo comprimido: %d bytes\n", tmn_arq_final);
    

    free(freq);
    free(fila);
}
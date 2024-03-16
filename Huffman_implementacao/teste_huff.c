#include "mapa/mapa.h"

int main(){

    char *nome_arquivo = (char*)malloc(100*sizeof(char));
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);
    int *freq = criar_freq();
    freq = contar_freq(nome_arquivo);
    Fila_prio *fila = criar_fila();
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0) enfileirar(fila, i, freq[i]);
    }
    criar_huff_tree(fila);
    huff_dict *dict = criar_huff_dict();
    gerar_mapa(fila->head, dict, 0);
    imprimir_caminho(fila->head, dict->path_bits, 0);
    return 0;
}
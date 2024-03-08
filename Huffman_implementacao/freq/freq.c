#include "freq.h"

int *criar_freq(){
    int *freq = calloc(256, sizeof(int));
    return freq;
}

int *contar_freq(char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if(arquivo == NULL){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }
    int *freq_arr = criar_freq();
    uchar byte;

    while(fscanf(arquivo, "%c", &byte) != EOF) freq_arr[byte]++;
    fclose(arquivo);
    return freq_arr;
}
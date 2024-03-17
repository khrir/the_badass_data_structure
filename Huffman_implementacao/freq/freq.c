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
    while(fread(&byte, sizeof(uchar), 1, arquivo) > 0) freq_arr[byte]++;
    fclose(arquivo);
    return freq_arr;
}

int *contar_freq_from_file(FILE *arquivo){
    if(arquivo == NULL){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }
    int *freq_arr = criar_freq();
    uchar byte;
    while(fread(&byte, sizeof(uchar), 1, arquivo) > 0) freq_arr[byte]++;
    fclose(arquivo);
    return freq_arr;
}
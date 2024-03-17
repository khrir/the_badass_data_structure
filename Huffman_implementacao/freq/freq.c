#include "freq.h"

ulli *criar_freq(){
    ulli *freq = (ulli *)calloc(256, sizeof(ulli));
    return freq;
}

ulli *contar_freq(char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if(arquivo == NULL){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }
    ulli *freq_arr = criar_freq();
    uchar byte;
    while(fread(&byte, sizeof(uchar), 1, arquivo) > 0) freq_arr[byte]++;
    fclose(arquivo);
    return freq_arr;
}

ulli *contar_freq_from_file(FILE *arquivo){
    if(arquivo == NULL){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }
    ulli *freq_arr = criar_freq();
    uchar byte;
    while(fread(&byte, sizeof(uchar), 1, arquivo) > 0) freq_arr[byte]++;
    fclose(arquivo);
    return freq_arr;
}

void print_freq(ulli *freq){
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0) printf("%c: %llu\n", (unsigned char)i, freq[i]);
    }
}
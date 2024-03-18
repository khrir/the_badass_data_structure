#include "freq.h"

/**
 * @brief Create a new frequency array
 * 
 * @return int* 
 */
int *criar_freq(){
    int *freq = calloc(256, sizeof(int));
    return freq;
}

/**
 * @brief Count the frequency of each byte in the file
 * 
 * @param nome_arquivo 
 * @return int* 
 */
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
 
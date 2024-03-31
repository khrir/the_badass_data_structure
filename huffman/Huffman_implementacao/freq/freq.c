#include "freq.h"

/**
 * @brief Create a new frequency array
 * 
 * @return int* 
 */
ulli *create_frequency_table(){
    ulli *frequencyTable = (ulli *)calloc(MAX_SIZE, sizeof(ulli));
    return frequencyTable;
}

/**
 * @brief Count the frequency of each byte in the file
 * 
 * @param nome_arquivo 
 * @return int* 
 */
void fill_frequency_table(ulli *frequencyTable, char *fileName){
    FILE *arquivo = fopen(fileName, "rb");

    if(arquivo == NULL){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }

    uchar byte;
    while(fread(&byte, sizeof(unsigned char), 1, arquivo) > 0) frequencyTable[byte]++;
    fclose(arquivo);
}
 
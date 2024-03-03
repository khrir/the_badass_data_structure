#include "freq.h"

ulli *criar_nova_freq(){
    ulli *freq = calloc(256,sizeof(ulli));
    return freq;
}

ulli *contar_frequencia(char *nome_arquivo){
    //Abre o arquivo para leitura, "rb" é para abrir o arquivo em modo binário
    FILE *arquivo = fopen(nome_arquivo,"rb");
    if(arquivo == NULL){
        puts("Erro ao abrir o arquivo");
        return NULL;
    }

    ulli *freq_arr = criar_nova_freq();
    uchar byte;
    //Lê o arquivo byte a byte
    while(fscanf(arquivo,"%c",&byte) != EOF) freq_arr[byte]++;
    fclose(arquivo);
    return freq_arr;
}

heap *criar_heap_freq(ulli *freq){
    heap *hp = criar_heap();
    for(int i = 0; i < 256; i++){
        if(freq[i]){
            unsigned char *byte = (unsigned char*)malloc(sizeof(unsigned char));
            *byte = i;
            push_heap(hp,byte,freq[i]);
        }
    }
    return hp;
}

 
int main(){
    char *nome_arquivo = (char*)malloc(100*sizeof(char));
    printf("Digite o nome do arquivo: ");
    scanf("%s",nome_arquivo);
    ulli *freq = contar_frequencia(nome_arquivo);
    heap *hp = criar_heap_freq(freq);
    if (check_heap(hp)) {
    printf("A propriedade da heap e atendida.\n");
    print_heap(hp);
    }
    free_heap(hp);
}


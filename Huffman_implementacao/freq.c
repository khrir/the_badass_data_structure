#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;
typedef ulli ulli;

/*Função que cria um vetor de frequência, o calloc foi utlizado para inicializar o vetor com 0
sem a necessidade de um for para inicializar o vetor nem a necessidade da chamada da funão memset*/
ulli *criar_nova_freq(){
    ulli *freq = calloc(256,sizeof(unsigned long long int));
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


//FALTA A ESCREVER A PARTE DA HEAP E FAZER A INTEGRAÇÃO DA HEAP COM O ARRAY DE FREQUENCIA
 

#include "decompress.h"

/**
 * @brief Read the header of the compressed file
 * 
 * @param arq_comprimido
 * @param cabecalho
 * @param tmn_lixo
 * @param tmn_arvore
 * @return void
 */

void ler_cabecalho(FILE *arq_comprimido, uchar *cabecalho, int *tmn_lixo, ulli *tmn_arvore){
    cabecalho[0] = fgetc(arq_comprimido);
    cabecalho[1] = fgetc(arq_comprimido);

    uchar lixinho = cabecalho[0] >> 5;
    memcpy(tmn_lixo, &lixinho, 0);

    cabecalho[0] = cabecalho[0] << 3;
    cabecalho[0] = cabecalho[0] >> 3;

    ulli avore = (cabecalho[1] << 5) | cabecalho[1]; 
    memcpy(tmn_arvore, &avore, 2);
}

/**
 * @brief Write the decompressed bytes in a file
 * 
 * @param arq_comprimido
 * @param arvore
 * @param tmn_lixo
 * @param arq_descomprimido
 * @return void
 */
void escr_bytes_descomp(FILE *arq_comprimido, Node_prio *arvore, int tmn_lixo, FILE *arq_descomprimido){
    Node_prio *node_atual = arvore;
    uchar byte, byte_aux;
    int cont_bit = 7;
    byte = fgetc(arq_comprimido);
    while(!feof(arq_comprimido)){
        byte_aux = fgetc(arq_comprimido);
        if(!feof(arq_comprimido)){
            while(cont_bit >= 0){
                if(encontrar_folhas(node_atual)){
                    fputc(node_atual->byte, arq_descomprimido);
                    node_atual = arvore;
                }
                if((1 << cont_bit) & byte) node_atual = node_atual->right;
                else node_atual = node_atual->left;
                cont_bit--;
            }
        }
        else{
            while(cont_bit >=(tmn_lixo - 1)){
                if(encontrar_folhas(node_atual)){
                    fputc(node_atual->byte, arq_descomprimido);
                    node_atual = arvore;
                }
                if((1 << cont_bit) & byte) node_atual = node_atual->right;
                else node_atual = node_atual->left;
                cont_bit--;
            }
        }
        cont_bit = 7;
        byte = byte_aux;
    }
    fclose(arq_descomprimido);
}

void ignorar_bytes(FILE *arquivo, int *lixo) {
    unsigned char byte;
    fread(&byte, sizeof(unsigned char), 1, arquivo);

    // Extrair o número de bytes a serem ignorados dos 3 bits mais significativos
    *lixo = (byte >> 5) & 0x07;

    // Ignorar os bytes especificados
    fseek(arquivo, *lixo, SEEK_CUR);
}

/**
 * @brief Decompress the file
 * 
 * @param arq_comprmido
 * @return void
 */

void descomprimir(char *arq_comprmido){
    int tmn_lixo;
    ulli tmn_arvore;
    uchar cabecalho[2];

    FILE *arq_comp = fopen(arq_comprmido, "rb");
    ler_cabecalho(arq_comp, cabecalho, &tmn_lixo, &tmn_arvore);

    Node_prio *arvore = NULL;
    arvore = construir_huff_from_file(arq_comp, arvore, &tmn_arvore);

    ignorar_bytes(arq_comp, &tmn_lixo); // Chama a função para ignorar os bytes conforme especificado

    char nome_arq_descomprimido[strlen(arq_comprmido)];
    strcpy(nome_arq_descomprimido, arq_comprmido);
    nome_arq_descomprimido[strlen(arq_comprmido) - 5] = '\0';
    
    escr_bytes_descomp(arq_comp, arvore, tmn_lixo, fopen(nome_arq_descomprimido, "wb"));

    free_huff_tree(arvore);
    fclose(arq_comp);
}

#include "mapa.h"

void gerar_mapa(Node_prio *node, huff_dict *dict, int nivel){
    if(node->left != NULL){
        dict->path_bits[nivel] = 0;
        gerar_mapa(node->left, dict, nivel + 1);
    }
    if(node->right != NULL){
        dict->path_bits[nivel] = 1;
        gerar_mapa(node->right, dict, nivel + 1);
    }
    if(node->left == NULL && node->right == NULL){
        for(int i = 0; i < nivel; i++) dict->mapa[node->byte][i] = dict->path_bits[i];
            dict->tmn[node->byte] = nivel;
            dict->freq[node->byte] = node->frequencia;
    }

}

void imprimir_caminho(Node_prio *node, int path_bits[], int nivel){
    if(node->left != NULL){
        path_bits[nivel] = 0;
        imprimir_caminho(node->left, path_bits, nivel + 1);
    }
    if(node->right != NULL){
        path_bits[nivel] = 1;
        imprimir_caminho(node->right, path_bits, nivel + 1);
    }
    if(node->left == NULL && node->right == NULL){
        printf("Caracter: %c, Caminho: ", node->byte);
        for(int i = 0; i < nivel; i++) printf("%d", path_bits[i]);
        printf("\n");
    }
}

int calc_lixo(huff_dict *dict){
    int bits = 0;
    for(int i = 0; i < 256; i++){
        if(dict->tmn[i] > 0){
            bits += dict->tmn[i] * dict->freq[i];
        }
    }
    int resto = bits % 8;
    return (resto > 0) ? 8 - resto : 0;
}
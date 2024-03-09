#ifndef MAPA_H
#define MAPA_H

#include  "../util/util.h"
#include "../huff/huff.h"
#include "../fila_prio/fila_prio.h" 

// Função que calcula o lixo
int calc_lixo(huff_dict *dict);

// Funcao que faz o "mapa" de 0's e 1's
void gerar_mapa(Node_prio *node, huff_dict *dict, int nivel);

// Funcao que imprime o caminho
void imprimir_caminho(Node_prio *node, int path_bits[], int nivel);


#endif
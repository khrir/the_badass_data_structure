#ifndef COMPRESS_H
#define COMPRESS_H


#include "../util/util.h"
#include "../code/code.h"
#include "../huff/huff.h"
#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"

// Função que comprime um arquivo
void comprimir(char *nome_arquivo);

#endif

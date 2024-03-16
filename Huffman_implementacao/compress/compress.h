#ifndef COMPRESS_H
#define COMPRESS_H


#include "../util/util.h"
#include "../code/code.h"
#include "../huff/huff.h"
#include "../fila_prio/fila_prio.h"
#include "../freq/freq.h"

// junta todas as funções de compressão para comprimir o arquivo
void comprimir(char *nome_arquivo);

#endif

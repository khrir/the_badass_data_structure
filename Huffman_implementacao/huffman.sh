#!/bin/bash

gcc -Wall -o huffman freq/freq.c fila_prio/fila_prio.c code/code.c compress/compress.c decompress/decompress.c huff/huff.c util/util.c huff_main.c

./huffman
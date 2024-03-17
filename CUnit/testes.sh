#!/bin/bash

gcc -Wall -o unit Huffman_implementacao/freq/freq.c CUnit/unity.c -lcunit

./unit
#include "util.h"

void print_byte(uchar byte){
    for(int i = 7; i >= 0; i--){
        printf("%d", (byte >> i) & 1);
    }
}
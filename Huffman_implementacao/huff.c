#include "huff.h"
#include "freq.h"


node_huff *new_node_huff(uchar byte, ulli freq, node_huff *left, node_huff *right){
    node_huff *new_node = (node_huff*)malloc(sizeof(node_huff));
    new_node->byte = byte;
    new_node->freq = freq;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

node_huff *constr_huff_tree(heap *hp){
    while(hp->size > 1){
        node_huff *left = pop_huff_hp(hp);
        node_huff *right = pop_huff_hp(hp);
        node_huff *new_node = new_node_huff('*',left->freq + right->freq,left,right);
        push_huff_hp(hp,new_node);
    }
    return pop_huff_hp(hp);
}

void print_pre_order(node_huff *node){
    if(node != NULL){
        if(node->byte != '*'){
            print_binary(node->byte);
            printf(" %d\n", node->freq);
        }else{
            printf("*\n", node->freq);
        }
        print_pre_order(node->left);
        print_pre_order(node->right);
    }
}
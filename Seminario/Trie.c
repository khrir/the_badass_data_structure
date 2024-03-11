#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NUM_CHARS 256 // Define um número de caracteres para a tabela ASCII

// Estrutura do nó da árvore, consiste em um vetor de ponteiros para os filhos e um booleano para indicar se é o fim de uma palavra. 
// Nos nós filhos, o índice do vetor representa o caractere da palavra, que aponta para o próximo nó da árvore.
typedef struct trie_node {
    struct trie_node *children[NUM_CHARS];
    bool is_end_of_word;
} trie_node;


//Função para criar um novo nó
trie_node *creat_node(){
    trie_node *new_node = malloc(sizeof(*new_node));

    for(int i = 0; i < NUM_CHARS; i++){
        new_node->children[i] = NULL;
    }

    new_node->is_end_of_word = false;
    return new_node;    
}

//Função para inserir uma palavra na árvore
bool trie_insert(trie_node *root, char *word){ // Root é a raiz da árvore
    int level;
    int length = strlen(word);

    if(root == NULL){
        root = creat_node();
    }

    trie_node *temp = root; // temp é um ponteiro temporário que aponta para a raiz, ele irá percorrar a árvore até encontrar o lugar certo para inserir a palavra

    for(level = 0; level < length; level++){
        int index = word[level];

        if(temp->children[index] == NULL){
            temp->children[index] = creat_node();
        }

        temp = temp->children[index];
    }

    if (temp->is_end_of_word){
        return false;
    } else {
        temp->is_end_of_word = true;
        return true;
    }
}

//Função para imprimir a árvore
void print_trie(trie_node *root, char *word, int level){
    if(root->is_end_of_word){
        word[level] = '\0';
        printf("%s\n", word);
    }

    for(int i = 0; i < NUM_CHARS; i++){
        if(root->children[i]){
            word[level] = i;
            print_trie(root->children[i], word, level + 1);
        }
    }
}

//Função de busca na árvore, retorna 1 se a palavra estiver na árvore e 0 caso contrário
bool search(trie_node *root, char *word){
    int level;
    int length = strlen(word);
    trie_node *temp = root;

    for(level = 0; level < length; level++){
        int index = word[level];

        if(temp->children[index] == NULL){
            return false;
        }

        temp = temp->children[index];
    }

    return (temp->is_end_of_word);
}   

int main(){

    trie_node *root = creat_node();
    char word[100];

    printf("Digite as palavras que deseja inserir na arvore (digite EOF para parar):\n");
    while(scanf("%s", word) != EOF){
        trie_insert(root, word);
    }

    //printf("Palavras inseridas na árvore:\n");
    //print_trie(root, word, 0);
    
    printf("Digite a palavra que deseja buscar na árvore:\n");
    scanf("%s", word);

    if (search(root, word) == 1){
        printf("A palavra %s esta na arvore\n", word);
    } else {
        printf("A palavra %s não esta na arvore\n", word);
    }

    return 0;   
}
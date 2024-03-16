#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NUM_CHARS 256 // Define um número de caracteres para a tabela ASCII

// Estrutura do nó da árvore, consiste em um vetor de ponteiros para os filhos e um booleano para indicar se é o fim de uma palavra. 
// Nos nós filhos, o índice do vetor representa o caractere da palavra, que aponta para o próximo nó da árvore.
typedef struct trie_node {
    struct trie_node *children[NUM_CHARS]; // Vetor de PONTEIROS para os filhos, possui 256 posições, uma para cada caractere da tabela ASCII.
    bool is_end_of_word; // Booleano para indicar se é o fim de uma palavra
} trie_node;


//Função para criar um novo nó
trie_node *creat_node(){
    trie_node *new_node = malloc(sizeof(*new_node));

    for(int i = 0; i < NUM_CHARS; i++){
        new_node->children[i] = NULL; // Inicializa todos o vetores de ponteiros para os filhos como NULL.
    }

    new_node->is_end_of_word = false; // Inicializa o booleano como falso, pois não é final de palavra. O mesmo só sera alterad na inserção de uma palavra.
    return new_node;    
}

//Função para inserir uma palavra na árvore
bool trie_insert(trie_node *root, char *word){ // Root é a raiz da árvore
    int level; // Nível da árvore
    int length = strlen(word); // Tamanho da palavra, que será correspondente ao nível em qual o fim da palavra será marcado.

    if(root == NULL){ // Se a raiz for NULL, e será no primeiro insert, cria um novo nó.
        root = creat_node(); // O primeiro caracter das palavra será sempre armaenado diretamente no nó raiz da árvore.
    }

    trie_node *temp = root; // temp é um ponteiro temporário que aponta para a raiz, ele irá percorrar a árvore até encontrar o lugar certo para inserir a palavra

    for(level = 0; level < length; level++){ // Percorre os níveis da árvore, até o nível correspondente ao tamanho da palavra. 
        int index = word[level]; //Index recebe o valor do caractere da palavra no nivel atual. É um número inteiro que representa o caractere na tabela ASCII.

        if(temp->children[index] == NULL){ // Se o nó filho correspondente ao caractere da palavra no nível atual for NULL, cria um novo nó
            temp->children[index] = creat_node(); // Agora o nó ocupa a posição correspondente ao caractere da palavra no nível atual.
        }

        temp = temp->children[index]; // atualiza temp para ser o nó filho correspondente ao caractere da palavra no nível atual.
    }

    // Quando o loop terminar, temp estará no nível correspondente ao tamanho da palavra, e o booleano is_end_of_word será alterado para true.
    if (temp->is_end_of_word){ // Se o booleano já for true, a palavra já está na árvore, então retorna false.
        return false; // retorna falso para garantir que não sejam inseridas palavras repetidas.
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
    int length = strlen(word); // comprimento da palavra
    trie_node *temp = root;

    for(level = 0; level < length; level++){
        int index = word[level]; //Index recebe o valor do caractere da palavra no nivel atual. É um número inteiro que representa o caractere na tabela ASCII.

        if(temp->children[index] == NULL){ //verifica se o index do vetor de filhos é nulo, se for, o caracter não está na árvore.
            return false;
        }

        temp = temp->children[index];
    }

    return (temp->is_end_of_word);
}   

int main(){

    trie_node *root = creat_node(); // Inicialia o nó raiz da árvore.
    char word[100];

    printf("Digite as palavras que deseja inserir na arvore (EOF para parar):\n\n");
    while(scanf("%s", word) != EOF){
        trie_insert(root, word);
    }

    //printf("Palavras inseridas na árvore:\n");
    //print_trie(root, word, 0);

    printf("Digite as palavra que deseja buscar na arvore (EOF para parar):\n\n");
    
    while(scanf("%s", word) != EOF){
        if (search(root, word) == 1){
            printf("A palavra %s esta na arvore\n\n", word);
        } else {
            printf("A palavra %s nao esta na arvore\n\n", word);
        }
    }

    return 0;   
}

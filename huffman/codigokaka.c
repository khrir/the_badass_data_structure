#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_SIZE 256

// Typedefs
typedef unsigned char uchar;
typedef unsigned long long int ulli;

typedef struct node {
    uchar byte;
    int frequencia;
    struct node *left, *right, *next;
} Node;

typedef struct list {
    Node *head;
    ulli current_size;
} List;

// Frequency
ulli *create_frequency_table() {
    ulli *frequencyTable = (ulli *)calloc(MAX_SIZE, sizeof(ulli));
    return frequencyTable;
}

void fill_frequency_table(ulli *frequencyTable, FILE *file) {
    uchar byte;

    while(fread(&byte, sizeof(unsigned char), 1, file) > 0){
        frequencyTable[byte]++;
    }
}

void print_frequency_table(ulli *frequencyTable) {
    for(int i = 0; i < MAX_SIZE; i++){
        if(frequencyTable[i] != 0){
            printf("%c: %llu\n", (uchar)i, frequencyTable[i]);
        }
    }
}

// Ordered List
void create_list(List *list) {
    list->head = NULL;
    list->current_size = 0;
}

void add_ordered_node(List *list, Node *node) {
    Node *current = list->head;
    Node *previous = NULL;

    if(current == NULL){
        list->head = node;
        node->next = NULL;
    } else if (node->frequencia < current->frequencia){
        node->next = current;
        list->head = node;
    } else {
        while(current != NULL && node->frequencia >= current->frequencia){
            previous = current;
            current = current->next;
        }
        if(previous != NULL) {
            previous->next = node;
        }
        node->next = current;
    }

    list->current_size++;
}

void fill_list(List *list, ulli *frequencyTable) {
    for(int i = 0; i < MAX_SIZE; i++){
        if(frequencyTable[i] != 0){
            Node *node = (Node *)malloc(sizeof(Node));
            node->byte = (uchar)i;
            node->frequencia = frequencyTable[i];
            node->left = NULL;
            node->right = NULL;
            node->next = NULL;

            add_ordered_node(list, node);
        }
    }
}

void print_node (Node *node) {
    printf("Caracter: %c | frequencia: %d\n", node->byte, node->frequencia);
}

void print_list(List *list) {
    Node *current = list->head;
    while(current != NULL){
        print_node(current);
        current = current->next;
    }
}

void free_list(List *list) {
    Node *current = list->head;
    while(current != NULL){
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

// Huffman
Node *remove_initial_node(List *list) {
    Node *aux = NULL;

    if(list->current_size > 0){
        aux = list->head;
        list->head = list->head->next;
        aux->next = NULL;
        list->current_size--;
    }

    return aux;
}

int is_leaf(Node *node) {
    return (node->left == NULL && node->right == NULL);
}

Node *create_huffman_tree(List *list) {
    Node *first, *second, *new_node;
    
    while(list->current_size > 1){
        first = remove_initial_node(list);
        second = remove_initial_node(list);
        new_node = (Node *)malloc(sizeof(Node));

        new_node->byte = '+';
        new_node->frequencia = first->frequencia + second->frequencia;
        new_node->left = first;
        new_node->right = second;
        new_node->next = NULL;

        add_ordered_node(list, new_node);
    }

    return list->head;
}

void print_huffman_tree(Node *root, int level) {
    if(is_leaf(root)){
        printf("Folha: %c | Altura: %d\n", root->byte, level);
    } else {
        print_huffman_tree(root->left, level + 1);
        print_huffman_tree(root->right, level + 1);
    }
}

// Dictionary
int calculate_tree_height(Node *root) {
    int left_height, right_height;

    if(root == NULL) return 0;

    left_height = calculate_tree_height(root->left) + 1;
    right_height = calculate_tree_height(root->right) + 1;

    return (left_height > right_height) ? left_height : right_height;
}

uchar **create_dictionary(int columns) {
    uchar **dictionary = (uchar **)malloc(MAX_SIZE * sizeof(uchar *));
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        dictionary[i] = (uchar *)calloc(columns, sizeof(uchar));
    }
    return dictionary;
}

void fill_dictionary(Node *root, uchar **dictionary, uchar *path, int columns) {
    uchar left[columns], right[columns];

    if(is_leaf(root)){
        strncpy(dictionary[root->byte], path, columns);
    } else {
        strncpy(left, path, columns);
        strncpy(right, path, columns);

        strncat(left, "0", columns - strlen(left) - 1);
        strncat(right, "1", columns - strlen(right) - 1);

        fill_dictionary(root->left, dictionary, left, columns);
        fill_dictionary(root->right, dictionary, right, columns);
    }
}

void print_dictionary(uchar **dictionary) {
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        if(strlen((char *)dictionary[i]) > 0){
            printf("%c: %s\n", (uchar)i, dictionary[i]);
        }
    }
}

void free_dictionary(uchar **dictionary) {
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        free(dictionary[i]);
    }
    free(dictionary);
}

// Codification
int calculate_string_size(uchar **dictionary, uchar *text) {
    int i, size = 0;
    while(text[i] != '\0'){
        size += strlen((char *)dictionary[text[i]]);
        i++;
    }
    return size;
}

uchar *file_to_string(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("Tamanho do arquivo: %ld bytes\n", size);
    uchar *string = (uchar *)calloc(size + 1, sizeof(uchar)); // +1 for null terminator

    if(string == NULL) {
        printf("Erro ao alocar memória para a string.\n");
        exit(1);
    }

    fread(string, sizeof(uchar), size, file);
    string[size] = '\0'; // Null terminate the string

    return string;
}

uchar *codify(uchar **dictionary, uchar *text) {
    int i = 0, size = calculate_string_size(dictionary, text);
    uchar *code = (uchar *)calloc(size + 1, sizeof(uchar)); // +1 for null terminator

    if (code == NULL) {
        printf("Erro ao alocar memória para o código.\n");
        exit(1);
    }

    while (text[i] != '\0') {
        strcat((char *)code, (char *)dictionary[text[i]]);
        i++;
    }
    return code;
}

void write_file(FILE *file, uchar *code) {
    fwrite(code, sizeof(uchar), strlen((char *)code), file);
}

// Decodification
uchar *decode(uchar *text, Node *root) {
    int i = 0;
    Node *current = root;
    uchar temp[2];
    uchar *decoded = (uchar *)calloc(strlen(text) + 1, sizeof(uchar));

    while (text[i] != '\0' && text[i] != '\n') {
        if (text[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (is_leaf(current)) {
            temp[0] = current->byte;
            temp[1] = '\0';
            strcat((char *)decoded, temp);
            current = root;
        }

        i++;
    }
    return decoded;
}


void free_huffman_tree(Node *root) {
    if (root != NULL) {
        free_huffman_tree(root->left);
        free_huffman_tree(root->right);
        free(root);
    }
}

// Main zone
FILE *open_file(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if(file == NULL){
        printf("Erro ao abrir o arquivo '%s'\n", filename);
        exit(1);
    }
    return file;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Ler arquivo
    FILE *file = open_file("public/teste.txt", "rb");

    // Frequência
    printf("Frequência:\n");
    ulli *frequencyTable = create_frequency_table();
    fill_frequency_table(frequencyTable, file);
    print_frequency_table(frequencyTable);
    printf("\n");

    // Lista Ordenada
    printf("Lista Ordenada:\n");
    List list;
    create_list(&list);
    fill_list(&list, frequencyTable);
    print_list(&list);
    printf("\n");

    // Huffman
    printf("Árvore Huffman:\n");
    Node *root = create_huffman_tree(&list);
    print_huffman_tree(root, 0);
    printf("\n");

    // Dicionário
    printf("Dicionário:\n");
    int columns = calculate_tree_height(root) + 1;
    uchar **dictionary = create_dictionary(columns);
    fill_dictionary(root, dictionary, "", columns);
    print_dictionary(dictionary);
    printf("\n");

    // Codificação
    uchar *text = file_to_string(file);
    uchar *code = codify(dictionary, text);
    printf("Código: %s\n", code);

    FILE *output = open_file("public/output.txt", "wb");
    write_file(output, code);
    fclose(output);

    // Decodificação
    FILE *encoded = open_file("public/output.txt", "r");
    uchar *encoded_text = file_to_string(encoded);

    uchar *decoded = decode(encoded_text, root);

    printf("Decodificado: %s\n", decoded);

    // Liberar memória alocada dinamicamente
    free(frequencyTable);
    free_list(&list);
    free_dictionary(dictionary);
    free(code);
    free(decoded);
    
    // free_huffman_tree(root);

    fclose(file);
    fclose(output);
    // fclose(encoded);

    return 0;
}
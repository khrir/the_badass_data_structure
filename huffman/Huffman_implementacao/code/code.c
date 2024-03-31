#include "code.h"

int calculate_altura(Node_prio *root) {
    int left_height, right_height;

    if(root == NULL) return 0;

    left_height = calculate_altura(root->left) + 1;
    right_height = calculate_altura(root->right) + 1;

    return (left_height > right_height) ? left_height : right_height;
}

int calculate_string_size(uchar **dictionary, uchar *text) {
    int i, size = 0;
    while(text[i] != '\0'){
        size += strlen((char *)dictionary[text[i]]);
        i++;
    }
    return size;
}

uchar **create_dictionary(int columns) {
    uchar **dictionary = (uchar **)malloc(MAX_SIZE * sizeof(uchar *));
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        dictionary[i] = (uchar *)calloc(columns, sizeof(uchar));
    }
    return dictionary;
}

void fill_dictionary(Node_prio *root, uchar **dictionary, uchar *path, int columns) {
    uchar left[columns], right[columns];

    if(root != NULL && root->left == NULL && root->right == NULL){
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

uchar *file_to_string(char *fileName){
    FILE *file = fopen(fileName, "rb");
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

uchar *codifica(uchar **dictionary, uchar *text) {
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

/**
 * @brief Create a new node
 * 
 * @param node 
 * @param item 
 * @return Node_lista* 
 */
Node_lista *novo_Node_lista(Node_lista *node, int item){
    Node_lista *new_node = (Node_lista*)malloc(sizeof(Node_lista));
    new_node->item = item;
    new_node->next = node;
    return new_node;
}

/**
 * @brief Remove a node from the list
 * 
 * @param node 
 * @return Node_lista* 
 */
Node_lista *remove_Node_lista(Node_lista *node){
    if (node == NULL) return NULL;
    Node_lista *next_node = node->next;
    free(node);
    return next_node;
}

/**
 * @brief Write the binary list in a file
 * 
 * @param arquivo 
 * @param node 
 * @return void
 */
void escrv_lista_bin(FILE *arquivo, Node_lista *node){
    if(node){
        escrv_lista_bin(arquivo, node->next);
        fprintf(arquivo, "%d", node->item);
    }
    return;
}

/**
 * @brief Create the way to the byte
 * 
 * @param arq_code 
 * @param node 
 * @param byte 
 * @param lista_bin 
 * @return void
 */
void gerar_caminho(FILE *arq_code, Node_prio *node, int byte, Node_lista *lista_bin){
    if(node){
        if(node->byte == byte && encontrar_folhas(node)){
            escrv_lista_bin(arq_code, lista_bin);
            return;
        }
        gerar_caminho(arq_code, node->left, byte, novo_Node_lista(lista_bin, 0));
        gerar_caminho(arq_code, node->right, byte, novo_Node_lista(lista_bin, 1));
    }
    else remove_Node_lista(lista_bin);
}

/**
 * @brief Write the tree in a file
 * 
 * @param nome_arquivo 
 * @param fila 
 * @return void
 */
void escrv_bits_cod(char *nome_arquivo, Node_prio *fila){
    FILE *arq_pai = fopen(nome_arquivo, "rb");
    FILE *arq_cod = fopen("bytes_code.txt", "wb");
    uchar byte_lido;
    size_t result;
    while((result = fread(&byte_lido, sizeof(uchar), 1, arq_pai)) > 0){
        gerar_caminho(arq_cod, fila, byte_lido, NULL);
    }
    fclose(arq_pai);
    fclose(arq_cod);
}

/**
 * @brief Calculate the trash size
 * 
 * @param nome_arquivo 
 * @return int
 */
int calc_lixo(uchar *code){
    int bits = strlen(code);
    int resto = bits % 8; 
    return (resto > 0) ? 8 - resto : 0;
}

/**
 * @brief Write the header of the file
 * 
 * @param tmn_lixo
 * @param tmn_arvore 
 * @param nome_arquivo 
 * @return void
 */

void escrever_cabecalho(int tmn_lixo, int tmn_arvore, char *nome_arquivo){
    uchar byte1, byte2;
    FILE *arquivo = fopen(nome_arquivo, "wb");
    byte1 = (tmn_lixo << 5) | (tmn_arvore >> 8);
    byte2 = tmn_arvore;
    fputc(byte1, arquivo);
    fputc(byte2, arquivo);
    fclose(arquivo);
}

void tamanho_extensao_arquivo(char *nome_arquivo, char *nome_arquivo_final) {
    uchar byte_extensao;
    FILE *arquivo = fopen(nome_arquivo_final, "ab"); // Abrindo o arquivo para escrita binária ao final

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo_final);
        return;
    }

    int tamanho_extensao;
    char *ponto = strrchr(nome_arquivo, '.');
    if (ponto == NULL) {
        puts("Arquivo sem extensão.\n");
        puts("Fechando o programa.\n");
        fclose(arquivo); // Fechar o arquivo antes de retornar
        return;
    } else {
        tamanho_extensao = strlen(ponto + 1);
        if (tamanho_extensao > 6) {
            puts("Não é possível! Tamanho de extensão é maior que o permitido\n");
            puts("Fechando o programa.\n");
            fclose(arquivo); // Fechar o arquivo antes de retornar
            return;
        }
    }

    byte_extensao = (uchar)(tamanho_extensao << 5);
 
    fwrite(&byte_extensao, sizeof(uchar), 1, arquivo);

    for (int i = 0; i < tamanho_extensao; i++){
        fwrite(&ponto[i+1], sizeof(uchar), 1, arquivo);
    }

    fclose(arquivo);
}

/**
 * @brief Save the tree in a file
 * 
 * @param nome_arquivo 
 * @param tmn_arvore
 * @param fila 
 * @return void
 */

void salvar_no_arquivo(char *nome_arquivo, int tmn_arvore, Fila_prio *fila, uchar *code){
    
    int tmn_lixo = calc_lixo(code);
    puts("Lixo calculado!");

    char *nome_arq_final = (char*)malloc(50*sizeof(char));
    strcpy(nome_arq_final, nome_arquivo);
    strcat(nome_arq_final, ".sccp");

    FILE *arq_final = fopen(nome_arq_final, "wb");
    escrever_cabecalho(tmn_lixo, tmn_arvore, nome_arq_final);
    puts("Cabecalho escrito!");

    salvar_huff_file(fila->head, nome_arq_final);
    puts("Arvore salva no arquivo!");

    tamanho_extensao_arquivo(nome_arquivo, nome_arq_final);
    puts("Tamanho da extensão do arquivo escrita!");
    fclose(arq_final);

    uchar *new_code = agrupar_bits(code);

    FILE *arquivo=fopen(nome_arq_final, "ab");
    fwrite(new_code, sizeof(uchar), strlen((char *)new_code) + 1, arquivo);
    fclose(arquivo);
    
    free(nome_arq_final);
}


uchar *agrupar_bits(uchar *code) {
    uchar *resultado = (uchar *)malloc((strlen((char *)code) / 8) * sizeof(uchar));
    if (resultado == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    int posicao_resultado = 0;
    uchar byte_atual = 0;
    int bits_no_byte_atual = 0;

    int tamanho = strlen((char *)code);
    for (int i = 0; i < tamanho; i++) {
        byte_atual |= (code[i] & 0x01) << (8 - 1 - bits_no_byte_atual);
        bits_no_byte_atual++;

        if (bits_no_byte_atual == 8) {
            resultado[posicao_resultado] = byte_atual;
            posicao_resultado++;
            byte_atual = 0;
            bits_no_byte_atual = 0;
        }
    }

    // Se houver bits restantes no último byte, preencha o byte e adicione-o ao resultado
    if (bits_no_byte_atual > 0) {
        resultado[posicao_resultado] = byte_atual;
    }

    return resultado;
}

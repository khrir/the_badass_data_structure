#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// List zone
typedef struct node {
    int number;
    struct node *next;
} Node;

typedef struct {
    Node *start;
    int current_size;
} List;

void create_list(List *list) 
{
    list->start = NULL;
    list->current_size = 0;
}

int is_empty(List *list) 
{
    return list->start == NULL;
}

void add_node(List *list, int number) 
{
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->number = number;
    new_node->next = NULL;

    if(is_empty(list)) {
        list->start = new_node;
        list->current_size++;
        return;
    }

    Node *current = list->start;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
    list->current_size++;
}

void search_node(List *list, int number) 
{
    if(is_empty(list)) {
        printf("Lista vazia\n");
        return;
    }

    int flag = 0;
    Node *current = list->start;
    while (current != NULL) {
        flag++;
        if(current->number == number) {
            printf("Encontrou: %d em %d comparacoes\n", current->number, flag);
            return;
        }
        current = current->next;
    }
    printf("Não está na lista\n");
}

int search_node_int(List *list, int number) 
{
    if(is_empty(list)) {
        printf("Lista vazia\n");
        return 0;
    }

    int flag = 0;
    Node *current = list->start;
    while (current != NULL) {
        flag++;
        if(current->number == number) {
            //printf("Encontrou: %d em %d comparacoes\n", current->number, flag);
            return flag;
        }
        current = current->next;
    }
    //printf("Não está na lista\n");
}

void print_list(List *list)


{
    if(is_empty(list)) {
        printf("Lista vazia\n");
        return;
    }

    printf("Size: %d\n", list->current_size);
    Node *current = list->start;
    while(current != NULL) {
        printf("%d ", current->number);
        current = current->next;
    }
}

void free_linked_list(List *list) {
    Node *current = list->start;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->start = NULL;
    list->current_size = 0;
}
// Binary Search Tree
typedef struct node_tree {
    int number;
    struct node_tree *left, *right;
} NodeTree;

int isset_node_tree(NodeTree *root, int number) {
    while (root != NULL)
    {
        if(root->number == number) {
            return number;
        }

        if (root->number > number) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return 0;
}

void add_node_tree(NodeTree **root, int number)
{
    if(*root == NULL) {
        *root = (NodeTree *) malloc (sizeof(NodeTree));
        (*root)->number = number;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else {
        if (!isset_node_tree(*root, number)) {
            if ((*root)->number > number) {
            add_node_tree(&((*root)->left), number);
            } else {
                add_node_tree(&((*root)->right), number);
            }
        }
    }
}

void search_node_tree(NodeTree *root, int number)
{
    int flag = 0;
    while (root != NULL)
    {
        flag++;
        if(root->number == number) {
            printf("Encontrou %d em %d comparacoes\n", root->number, flag);
            return;
        }

        if (root->number > number) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    printf("Nao esta na arvore\n");
}

int search_node_tree_int(NodeTree *root, int number)
{
    int flag = 0;
    while (root != NULL)
    {
        flag++;
        if(root->number == number) {
            //printf("Encontrou %d em %d comparacoes\n", root->number, flag);
            return flag;
        }

        if (root->number > number) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    //printf("Nao esta na arvore\n");
}

void print_tree(NodeTree *root) 

{
    if(root) {
        print_tree(root->left);
        printf("%d ", root->number);
        print_tree(root->right);
    }
}
// intersection zone
void add_node_by_terminal(List *list, NodeTree **root)
{
    int number, qtd;
    // printf("Entre com a quantidade que deseja inserir: ");
    scanf("%d", &qtd);

    while (qtd > 0)
    {
        srand(time(NULL));
        number = rand() % qtd;

        add_node(list, number);
        add_node_tree(root, number);
        qtd--;
    }
}

void search_node_by_randint(List *list, NodeTree *root)
{
    if(is_empty(list)) {
        printf("Lista vazia\n");
        return;
    }

    srand(time(NULL)); // Seed para geração de números aleatórios

    int random_number = rand() % (list->current_size) + 1;
    printf("Número aleatório gerado: %d\n", random_number);

    search_node(list, random_number);
    search_node_tree(root, random_number);
}

void search_node_by_terminal(List *list, NodeTree *root) 

{
    int number;
    printf("Entre com o valor que deseja procurar: ");
    scanf("%d", &number);

    search_node(list, number);
    search_node_tree(root, number);
}

void free_binary_tree(NodeTree *root) {
    if (root == NULL) {
        return;
    }
    free_binary_tree(root->left);
    free_binary_tree(root->right);
    free(root);
}

void add_average(List *list, NodeTree **root){
    int qtd, start = 1, random_num;
    scanf("%d", &qtd);
    FILE *comparative_file = comparative_file = fopen("comparative_file.txt", "w");
    fprintf(comparative_file, "lista abb tam\n");

    /*se qtd(tamanho da lista) for 10
    esse for vai rodar de 1 ate 10
    o primeiro for interno vai rodar de 0 ate 9 inserindo um numero aleatorio
    no intervalo de i (10) e vai adicionar na lista e na arvore*/
    
        for(int i = start; i <= qtd; i+=start){
            for(int j = 0; j <= i; j+=1){
                random_num = rand() % i;
                add_node(list, random_num);
                add_node_tree(root, random_num);
            }

    /*Esse segundo for vai fazer a media de comparações
    se i = 2, por exemplo, na primeira iteração(j=0) ele vai achar um numero aleatorio
    no intervalo 2, e vai procurar ele na lista. Na segunda iteração(j=1), ele vai fazer isso de novo
    assim ate chegar em 99
    depois disso eu vou pegar o numero total de comparações de cada estrutura e dividir por 100 pra achar a media
    */

        int cont_list = 0, cont_tree = 0;
        for(int j = 0; j < 100; j++){
            random_num = rand() % i;
            cont_list += search_node_int(list, random_num);
            cont_tree += search_node_tree_int(*root, random_num);
        }

        printf("%d %d %d\n",(int)cont_list/100, (int)cont_tree/100, i);
        fprintf(comparative_file, "%d %d %d\n", (int)cont_list/100, (int)cont_tree/100, i);
        free_linked_list(list);
        free_binary_tree(*root);
        *root = NULL; //o free destroi a arvore toda
    }
    fclose(comparative_file);
}

void menu(List *list, NodeTree **root)
{
    int opcao;
    do {
        system("clear");
        printf("------------- Latitude 10 -------------\n");
        printf("1 - Inserir na lista\n2 - Imprimir a lista\n3 - Buscar na lista\n4 - Média\n5 - Sair");
        printf("\n\n");

        scanf("%d", &opcao);
        switch (opcao) {
        case 1:
            add_node_by_terminal(list, root);
            break;
        case 2:
            printf("Lista\n");
            print_list(list);
            printf("\n");
            printf("Arvore\n");
            print_tree(*root);
            printf("\n");
            sleep(10);
            break;
        case 3:
            // search_node_by_terminal(list, *root);
            search_node_by_randint(list, *root);
            sleep(5);
            break;
        case 4:
            add_average(list, root);
            sleep(10);
            break;
        case 5:
            printf("Encerrando o programa...\n");
            opcao = 0;
            break;
        }

    } while (opcao != 0);
}

int main () 
{
    List list;
    create_list(&list);

    NodeTree *root = NULL;

    // add_node_by_terminal(&list, &root);
    menu(&list, &root);

    return 0;
}
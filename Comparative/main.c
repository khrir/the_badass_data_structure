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

// Binary Search Tree
typedef struct node_tree {
    int number;
    struct node_tree *left, *right;
} NodeTree;

void add_node_tree(NodeTree **root, int number)
{
    if(*root == NULL) {
        *root = (NodeTree *) malloc (sizeof(NodeTree));
        (*root)->number = number;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else {
        if ((*root)->number > number) {
            add_node_tree(&((*root)->left), number);
        } else {
            add_node_tree(&((*root)->right), number);
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
        scanf("%d", &number);

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

void menu(List *list, NodeTree **root)
{
    int opcao;
    do {
        system("clear");
        printf("------------- Latitude 10 -------------\n");
        printf("1 - Inserir na lista\n2 - Imprimir a lista\n3 - Buscar na lista");
        printf("\n\n");

        scanf("%d", &opcao);
        switch (opcao) {
        case 1:
            add_node_by_terminal(list, root);
            break;
        case 2:
            print_list(list);
            printf("\n");
            print_tree(*root);
            printf("\n");
            sleep(10);
            break;
        case 3:
            // search_node_by_terminal(list, *root);
            search_node_by_randint(list, *root);
            sleep(10);
            break;
        default:
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
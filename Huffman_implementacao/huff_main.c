#include "compress/compress.h"
#include "decompress/decompress.h"

int main(){
    system("chcp 65001");
    limpar_tela();
    int opcao;

    while(opcao != 3){
        printf(" _    _  _    _  ______  ______  __  __            _   _ \n");
    printf("| |  | || |  | ||  ____||  ____||  \\/  |    /\\    | \\ | |\n");
    printf("| |__| || |  | || |__   | |__   | \\  / |   /  \\   |  \\| |\n");
    printf("|  __  || |  | ||  __|  |  __|  | |\\/| |  / /\\ \\  | . ` |\n");
    printf("| |  | || |__| || |     | |     | |  | | / ____ \\ | |\\  |\n");
    printf("|_|  |_| \\____/ |_|     |_|     |_|  |_|/_/    \\_\\|_| \\_|\n\n\n");
    
        printf("1. Comprimir\n2. Descomprimir\n3. Sair\n> ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1:
                limpar_tela();
                printf("Digite o nome do arquivo que deseja comprimir:\n");
                    char *nome_arquivo_comp = input();
                    if(!comprimir(nome_arquivo_comp)) break;
                    puts("");
                    puts("Arquivo comprimido com sucesso e salvo no diretorio do programa.");
                    puts("");
                    puts("E VAI CORINTHIANS!");
                    print_art1();
                    puts("");
                    puts("Pressione Enter para continuar.");
                    if(getchar() == 10) limpar_tela();
                break;
            case 2:
                limpar_tela();
                printf("Digite o nome do arquivo que deseja descomprimir:\n");
                    char *nome_arquivo_desc = input();
                    descomprimir(nome_arquivo_desc);
                    puts("");
                    puts("Arquivo descomprimido com sucesso e salvo no diretorio do programa.");
                    puts("");
                    puts("Pressione Enter para continuar.");
                    if(getchar() == 10) limpar_tela();
                break;
            case 3:
                print_art2();
                puts("");
                puts("VAI EMBORA NE? TMJ");                
                puts("Pressione enter para sair.");
                if(getchar() == 10){
                    exit(0);
                }
                break;
            default:
                printf("Entrada invalida.\n");
                break;
        }

    
    }
    return 0;
}
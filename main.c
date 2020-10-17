//Grupo Raiz
#include <stdio.h>
#include <stdlib.h>
//#include "./patricia/lib/patricia.c"
//#include "./tst/lib/tst.c"
#include "leitura.c"

int main () {
    int x = -1, y = -1, qtdComp = 0;
    char palavra[256];
    Patricia patricia = NULL;
    TST tst = NULL;

    while(y != 0 && x != 0) {
        x = -1;
        qtdComp = 0;
        printf("\n");
        printf("          --- MENU ---        \n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1. TST                        \n");
        printf("2. Patricia                   \n");
        printf("0. Sair                       \n");
        
        printf("Operacao Escolhida: ");
        scanf("%d", &y);
        printf("\n");
        
        while (x != 5 && x != 0 && y > 0 && y<=2) {
            printf("\n");
            if(y==1) printf("       --- MENU TST ---     \n");
            else     printf("    --- MENU Patricia ---   \n");
            printf("Escolha uma das opcoes abaixo:       \n");
            printf("1. Inserir palavra                   \n");
            printf("2. Pesquisar palavra                 \n");
            printf("3. Exibir em Ordem Alfabetica        \n");
            printf("4. Contar Palavras                   \n");
            printf("5. Escolher outra arvore             \n");
            printf("0. Sair                              \n");
            printf("\n");

            printf("Operacao Escolhida: ");
            scanf("%d", &x);
            printf("\n");

            switch (y) {
            case 1:
                switch  (x) {
                    case 1:
                        //printf("Qual palavra deseja inserir?\n");
                        //scanf("%s", palavra);
                        //tst_insert(&tst, palavra);
                        qtdComp = 0;
                        tst_ler_arquivo(&tst, &qtdComp);
                        printf("Quantidade de comparacoes para insercao: %d", qtdComp);
                        break;
                    case 2:
                        qtdComp = 0;
                        printf("Qual palavra deseja pesquisar?\n");
                        scanf("%s", palavra);
                        printf(tst_search(&tst, palavra, &qtdComp) ? "Palavra presente na arvore\n":"Palavra nao esta na arvore\n");
                        printf("Quantidade de comparacoes pesquisa: %d\n", qtdComp);
                        break;
                    case 3:
                        printf("Exibindo em Ordem Alfabetica:\n");
                        tst_print(tst);
                        break;
                    case 4:
                        printf("Total de palavras na arvore: %d\n", tst_word_count(tst));
                    default:
                        break;
                }
                break;
            case 2:
                switch  (x) {
                    case 1:
                        //printf("Qual palavra deseja inserir?\n");
                        //scanf("%s", palavra);
                        //patricia = pat_insert(&patricia, palavra);
                        qtdComp = 0;
                        patricia_ler_arquivo(&patricia, &qtdComp);
                        printf("Quantidade de comparacoes para insercao: %d", qtdComp);
                        break;
                    case 2:
                        qtdComp = 0;
                        printf("Qual palavra deseja pesquisar?\n");
                        scanf("%s", palavra);
                        printf(pat_search(patricia, palavra, &qtdComp) ? "Palavra presente na arvore\n":"Palavra nao esta na arvore\n");
                        printf("Quantidade de comparacoes pesquisa: %d\n", qtdComp);
                        break;
                    case 3:
                        printf("Exibindo em Ordem Alfabetica:\n");
                        pat_print(patricia);
                        break;
                    case 4:
                        printf("Total de palavras na arvore: %d\n", pat_word_count(patricia));
                    default:
                        break;
                }
                break;            
            default:
                break;
            }
        }
    }
    return 0;
}
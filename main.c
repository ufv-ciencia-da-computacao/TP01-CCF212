//Grupo Raiz
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./patricia/lib/patricia.h"
#include "./tst/lib/tst.h"
#include "leitura.c"

int main () {
    int x = -1, y = -1;
    char palavra[256];
    Patricia patricia = NULL;
    TST tst = NULL;
    clock_t t;
    double tempoTotal;

    benchmark_t benchmark;
    benchmark_init(&benchmark);

    while(y != 0 && x != 0) {
        benchmark_init(&benchmark);
        x = -1;
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
                        benchmark_init(&benchmark);
                        t = clock();
                        tst_ler_arquivo(&tst, &benchmark);
                        t = clock() - t;
                        tempoTotal = ((double)t)/CLOCKS_PER_SEC;
                
                        benchmark_print_qtd_comp(benchmark);
                        tst_mem_size(tst, &benchmark);
                        benchmark_print_mem_insertion(benchmark);
                        printf("Tempo gasto para insercao: %f segundos\n", tempoTotal);
                        break;
                    case 2:
                        benchmark_reset_qtd_comp(&benchmark);
                        printf("Qual palavra deseja pesquisar?\n");
                        scanf("%s", palavra);

                        t = clock();
                        printf(tst_search(&tst, palavra, &benchmark) ? "Palavra presente na arvore\n":"Palavra nao esta na arvore\n");
                        t = clock() - t;
                        tempoTotal = ((double)t)/CLOCKS_PER_SEC;
                        
                        benchmark_print_qtd_comp(benchmark);

                        printf("Tempo gasto para pesquisa: %f segundos\n", tempoTotal);
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
                        benchmark_init(&benchmark);
                        t = clock();
                        patricia_ler_arquivo(&patricia, &benchmark);
                        t = clock() - t;
                        tempoTotal = ((double)t)/CLOCKS_PER_SEC;
                        
                        benchmark_print_qtd_comp(benchmark);
                        pat_mem_size(patricia, &benchmark);
                        benchmark_print_mem_insertion(benchmark);
                        printf("Tempo gasto para insercao: %f segundos\n", tempoTotal);
                        break;
                    case 2:
                        benchmark_reset_qtd_comp(&benchmark);
                        printf("Qual palavra deseja pesquisar?\n");
                        scanf("%s", palavra);
                        t = clock();
                        printf(pat_search(patricia, palavra, &benchmark) ? "Palavra presente na arvore\n":"Palavra nao esta na arvore\n");
                        t = clock() - t;
                        tempoTotal = ((double)t)/CLOCKS_PER_SEC;
                       
                        benchmark_print_qtd_comp(benchmark);

                        printf("Tempo gasto para pesquisa: %f segundos\n", tempoTotal);
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
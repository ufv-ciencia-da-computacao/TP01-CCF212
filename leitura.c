//Grupo Raiz
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
//#include "./benchmark/lib/benchmark.c"
#include "./patricia/lib/patricia.c"
#include "./tst/lib/tst.c"

void tst_ler_arquivo (TST* tst, benchmark_t *b, double* temp) {
    FILE* arq;
    int qtdPalavra = 0;
    clock_t t;
    char palavra[256], nome[50];
    (*temp) = 0;
    
    printf("Qual o nome do arquivo? (com a extensao)\n");
    scanf("%s", nome);
    arq = fopen(nome, "r");

    if(arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
    } else {
        char palavra[256];

        while(!feof(arq)) {
            fscanf(arq, "%s", palavra);
            for(int i = 0; palavra[i]; i++){
                palavra[i] = tolower(palavra[i]);
            }
            t = clock();
            tst_insert(tst, palavra, b);
            t = clock() - t;
            (*temp) += t;
        }

        fclose(arq);
    }
}

void patricia_ler_arquivo (Patricia* patricia, benchmark_t* b, double* temp) {
    FILE* arq;
    char palavra[256], nome[50];
    clock_t t;
    (*temp) = 0;
    printf("Qual o nome do arquivo? (com a extensao)\n");
    scanf("%s", nome);
    arq = fopen(nome, "r");

    if(arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
    } else {
        char palavra[256];

        while(!feof(arq)) {
            fscanf(arq, "%s", palavra);

            for(int i = 0; palavra[i]; i++){
                palavra[i] = tolower(palavra[i]);
            }
            t = clock();
            (*patricia) = pat_insert(patricia, palavra, b);
            t = clock() - t;
            (*temp) += t;
        }

        fclose(arq);
    }
}
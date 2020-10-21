//Grupo Raiz
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./benchmark/lib/benchmark.h"
#include "./patricia/lib/patricia.h"
#include "./tst/lib/tst.h"

void tst_ler_arquivo (TST* tst, benchmark_t *b) {
    FILE* arq;
    int qtdPalavra = 0;
    char palavra[256], nome[50];
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
            tst_insert(tst, palavra, b);
        }

        fclose(arq);
    }
}

void patricia_ler_arquivo (Patricia* patricia, benchmark_t* b) {
    FILE* arq;
    char palavra[256], nome[50];
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
            (*patricia) = pat_insert(patricia, palavra, b);
        }

        fclose(arq);
    }
}
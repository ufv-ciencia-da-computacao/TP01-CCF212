//Grupo Raiz
#include<stdio.h>
#include "./patricia/lib/patricia.c"
#include "./tst/lib/tst.c"

void tst_ler_arquivo (TST* tst, int* qtdComp) {
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
            qtdPalavra = 0;
            fscanf(arq, "%s", palavra);
            strcpy(palavra, strlwr(palavra));
            tst_insert(tst, palavra, &qtdPalavra);
            (*qtdComp) += qtdPalavra;
        }

        fclose(arq);
    }
}

void patricia_ler_arquivo (Patricia* patricia, int* qtdComp) {
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
            qtdPalavra = 0;
            fscanf(arq, "%s", palavra);
            strcpy(palavra, strlwr(palavra));
            (*patricia) = pat_insert(patricia, palavra, &qtdPalavra);
            (*qtdComp) += qtdPalavra;
        }

        fclose(arq);
    }
}
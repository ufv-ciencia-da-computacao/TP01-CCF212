//Grupo Raiz
#include "benchmark.h"
#include <time.h>

//Função para inicialização da contagem de memória e comparações
void benchmark_init(benchmark_t *b) {
    b->mem_insertion=0;
    b->qtd_comp=0;
}

//Função para resetar a contagem de memória alocada
void benchmark_reset_mem_insertion(benchmark_t *b) {
    b->mem_insertion = 0;
}

//Função para resetar a contagem de comparações
void benchmark_reset_qtd_comp(benchmark_t *b) {
    b->qtd_comp = 0;
}

//Função para somar quantidade de comparações 
void benchmark_sum_qtd_comp(benchmark_t *b, int qtd_comp) {
    b->qtd_comp += qtd_comp;
}

//Função para somar memória alocada
void benchmark_sum_mem_insertion(benchmark_t *b, size_t mem_insert) {
    b->mem_insertion += mem_insert;
}

//Função para impressão da memória total alocada
void benchmark_print_mem_insertion(benchmark_t b) {
    printf("Quantidade de memoria alocada: %ld bytes\n", b.mem_insertion);
}

//Função para impressão da quantidade de comparações
void benchmark_print_qtd_comp(benchmark_t b) {
    printf("\nQuantidade de comparacoes: %d\n", b.qtd_comp);
}

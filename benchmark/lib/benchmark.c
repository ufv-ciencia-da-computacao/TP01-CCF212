#include "benchmark.h"
#include <time.h>

void benchmark_init(benchmark_t *b) {
    b->mem_insertion=0;
    b->qtd_comp=0;
}

void benchmark_reset_mem_insertion(benchmark_t *b) {
    b->mem_insertion = 0;
}

void benchmark_reset_qtd_comp(benchmark_t *b) {
    b->qtd_comp = 0;
}

void benchmark_sum_qtd_comp(benchmark_t *b, int qtd_comp) {
    b->qtd_comp += qtd_comp;
}

void benchmark_sum_mem_insertion(benchmark_t *b, size_t mem_insert) {
    b->mem_insertion += mem_insert;
}

void benchmark_print_mem_insertion(benchmark_t b) {
    printf("Quantidade de memoria alocada: %ld bytes\n", b.mem_insertion);
}

void benchmark_print_qtd_comp(benchmark_t b) {
    printf("\nQuantidade de comparacoes para insercao: %d\n", b.qtd_comp);
}

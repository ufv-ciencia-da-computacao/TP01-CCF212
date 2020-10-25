//Grupo Raiz
#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <stdio.h>
#include <stdlib.h>

/*estrutura para facilitar o armazenamento
e passagem de parâmetros para calculo de
comparações e memória alocada*/
typedef struct {
    int qtd_comp;
    size_t mem_insertion;
} benchmark_t;

void benchmark_init(benchmark_t *b);
void benchmark_reset_qtd_comp(benchmark_t *b);
void benchmark_reset_mem_insertion(benchmark_t *b);
void benchmark_sum_qtd_comp(benchmark_t *b, int qtd_comp);
void benchmark_sum_mem_insertion(benchmark_t *b, size_t mem_insertion);
void benchmark_print_mem_insertion(benchmark_t b);
void benchmark_print_qtd_comp(benchmark_t b);

#endif
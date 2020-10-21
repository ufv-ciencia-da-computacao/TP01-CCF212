//Grupo Raiz
#ifndef __TST_H__
#define __TST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../benchmark/lib/benchmark.h"

typedef struct node_t *TST;

struct node_t {
  struct node_t *left;
  struct node_t *right;
  struct node_t *middle;
  char character;
  int end_word;
};

void tst_node_init(TST *root, char ch);
void tst_insert(TST *root, char *str, benchmark_t* b);
int tst_search(TST *root, char *str, benchmark_t* b);
void tst_print(TST root);
int tst_word_count (TST root);
void tst_mem_size(TST tst, benchmark_t *b);
#endif
//Grupo Raiz
#ifndef __PATRICIA_H__
#define __PATRICIA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../benchmark/lib/benchmark.h"

#define D 8 // Depends on type of Item
#define CHARACTERS 256

typedef char* String;
typedef int index_amp;

//Enumeração que define o tipo de um nó, interno(0) ou externo(1)
typedef enum {
  internal, external
} node_type;

/*
estrutura base utilizada por uma árvore Patricia, a partir da implementação proposta por Ziviani
Modificações: armazena caracter para comparação e índice em nós internos
*/
typedef struct pat_node_str* Patricia;
typedef struct pat_node_str {
  node_type type;
  union {
    //nó interno
    struct {
      char character; //armazena o caracter a ser comparado
      index_amp index; //armazena o índice a ser comparado
      Patricia left;
      Patricia right;
    }node_internal;
    //nó externo
    String key; //armazena palavra
  }node;
} pat_node;

int type_node(Patricia p);
void pat_init(Patricia* patricia);
void pat_print(Patricia patricia);
int pat_word_count (Patricia patricia);
int pat_search(Patricia patricia, String key, benchmark_t* b);
Patricia pat_insert(Patricia* patricia, String key, benchmark_t* b);
void pat_mem_size(Patricia pat, benchmark_t *b);
void pat_remove_nodes(Patricia *pat);
#endif
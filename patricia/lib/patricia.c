//Grupo Raiz
#include "patricia.h"
#include "../../benchmark/lib/benchmark.h"

typedef struct {
  int index;
  char character;
} tuple_t;

int min(int a, int b) {
  return (a < b ? a : b);
}

tuple_t get_char(Item a, Item b, benchmark_t* bench) {
  size_t item_a = strlen(a);
  size_t item_b = strlen(b);

  tuple_t tuple;

  int m = min(item_a, item_b);

  for(int i=0; i<m; i++) {
    benchmark_sum_qtd_comp(bench, 1);
    if (a[i] == '\0') {
      benchmark_sum_qtd_comp(bench, 1);
      tuple.character = a[i];
      tuple.index = i;
      return tuple;
    } else if(b[i] == '\0') {
      benchmark_sum_qtd_comp(bench, 1);
      tuple.character = b[i];
      tuple.index = i;
      return tuple;
    } else if (a[i] != b[i]) {
      benchmark_sum_qtd_comp(bench, 3);
      if (a[i] <= b[i]) {
        benchmark_sum_qtd_comp(bench, 1);
        tuple.character = a[i];
      } else {
        benchmark_sum_qtd_comp(bench, 1);
        tuple.character = b[i];
      }      
      tuple.index = i;
      return tuple;
    }
    benchmark_sum_qtd_comp(bench, 3);
  }
}

int type_node(Patricia p) {
  return (p->type);
}

Patricia pat_init_internal(Patricia* left, Patricia *right, tuple_t tuple) { 
  Patricia patricia;
  (patricia) = (Patricia) malloc(sizeof(pat_node));

  (patricia)->node.node_internal.character = tuple.character;
  (patricia)->node.node_internal.index = tuple.index;
  (patricia)->node.node_internal.left = *left;
  (patricia)->node.node_internal.right = *right;
  (patricia)->type = internal;
  return patricia;
}

void pat_init_external(Patricia *patricia, Item key) {
  (*patricia) = (Patricia) malloc(sizeof(pat_node));
  (*patricia)->type = external;
  strcpy((*patricia)->node.key, key);
}

int pat_search(Patricia patricia, Item key, benchmark_t* b) {
  benchmark_sum_qtd_comp(b, 1);
  if (type_node(patricia) == external) {
    benchmark_sum_qtd_comp(b, 1);
    return strcmp(key, patricia->node.key) == 0 ? 1:0;
  }

  if (key[patricia->node.node_internal.index] <= patricia->node.node_internal.character)  {
    benchmark_sum_qtd_comp(b, 1);
    return pat_search(patricia->node.node_internal.left, key, b);
  } else {
    benchmark_sum_qtd_comp(b, 1);
    return pat_search(patricia->node.node_internal.right, key, b);
  }
}

void pat_print(Patricia patricia) {
  if (patricia == NULL) return;
  
  if (type_node(patricia) == internal) pat_print(patricia->node.node_internal.left);
  if (type_node(patricia) == external) puts(patricia->node.key); 
  if (type_node(patricia) == internal) pat_print(patricia->node.node_internal.right);
}

int word_countP(Patricia patricia, int count) {
  if (patricia == NULL) return count;
  
  if (type_node(patricia) == internal) count = word_countP(patricia->node.node_internal.left, count);
  if (type_node(patricia) == external) return count+1;
  if (type_node(patricia) == internal) count = word_countP(patricia->node.node_internal.right, count);
}

int pat_word_count(Patricia patricia) {
  return word_countP(patricia, 0);
}

Patricia pat_insert_node_internal(Patricia* patricia, Item key, tuple_t tuple, benchmark_t* b) {
  Patricia new;
  if (type_node(*patricia) == external || tuple.index < (*patricia)->node.node_internal.index) {
    benchmark_sum_qtd_comp(b, 2);
    pat_init_external(&new, key);
    if (key[tuple.index] > tuple.character) {
      benchmark_sum_qtd_comp(b, 1);
      return pat_init_internal(patricia, &new, tuple);
    } else {
      benchmark_sum_qtd_comp(b, 1);
      return pat_init_internal(&new, patricia, tuple);
    }
  } else {
    benchmark_sum_qtd_comp(b, 2);
    if (key[(*patricia)->node.node_internal.index] >  (*patricia)->node.node_internal.character) {
      benchmark_sum_qtd_comp(b, 1);
      (*patricia)->node.node_internal.right = 
              pat_insert_node_internal(&(*patricia)->node.node_internal.right, key, tuple, b);
    } else {
      benchmark_sum_qtd_comp(b, 1);
      (*patricia)->node.node_internal.left = 
              pat_insert_node_internal(&(*patricia)->node.node_internal.left, key, tuple, b);
    }
    return (*patricia);
  }
}

Patricia pat_insert(Patricia* patricia, Item key, benchmark_t* b) {

  benchmark_sum_qtd_comp(b, 1);
  if((*patricia) == NULL) {
    pat_init_external(patricia, key);
    return (*patricia);
  } 
  
  Patricia aux = *patricia;

  while (type_node(aux) != external) {
    benchmark_sum_qtd_comp(b, 1);
    if (key[aux->node.node_internal.index] > aux->node.node_internal.character) {
      benchmark_sum_qtd_comp(b, 1);
      aux = aux->node.node_internal.right;
    } else {
      benchmark_sum_qtd_comp(b, 1);
      aux = aux->node.node_internal.left;
    }
  }
  benchmark_sum_qtd_comp(b, 1);

  tuple_t tuple = get_char(key, aux->node.key, b);

  return pat_insert_node_internal(patricia, key, tuple, b);  
}

int pat_count_nodes(Patricia pat) {
  if (pat == NULL) return 0;
  if (type_node(pat) == external) return 1;
  return 1 + pat_count_nodes(pat->node.node_internal.left) + pat_count_nodes(pat->node.node_internal.right);
}

void pat_mem_size(Patricia pat, benchmark_t *b) {
  benchmark_sum_mem_insertion(b, sizeof(pat_node)*pat_count_nodes(pat));
}

void pat_remove_nodes(Patricia *pat) {
  if((*pat)==NULL) return;

  if (type_node((*pat)) == external) {
    free((*pat));
    *pat=NULL;
    return;
  }

  pat_remove_nodes(&(*pat)->node.node_internal.left);
  pat_remove_nodes(&(*pat)->node.node_internal.right);
  free((*pat));
  *pat=NULL;
} 
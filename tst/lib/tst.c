//Grupo Raiz
#include "tst.h"
#include "../../benchmark/lib/benchmark.h"

void tst_node_init(TST *root, char ch) {
  (*root) = (TST) malloc(sizeof(struct node_t));

  (*root)->left = NULL;
  (*root)->middle = NULL;
  (*root)->right = NULL;
  (*root)->end_word = 0;
  (*root)->character = ch;
}

static void insert(TST *root, char* str, int pos, int len, benchmark_t *b) {
  benchmark_sum_qtd_comp(b, 1);
  if ((*root) == NULL) {
      tst_node_init(root, str[pos]);
    }

  benchmark_sum_qtd_comp(b, 1);
  if (pos == len) {
    (*root)->end_word = 1;
    return;
  }

  if (str[pos] == (*root)->character) {
    benchmark_sum_qtd_comp(b, 1);
    insert(&(*root)->middle, str, pos+1, len, b);
  } else if (str[pos] > (*root)->character) {
    benchmark_sum_qtd_comp(b, 2);
    insert(&(*root)->right, str, pos, len, b);
  } else {
    benchmark_sum_qtd_comp(b, 2);
    insert(&(*root)->left, str, pos, len, b);
  }
  
}

//Operação de inserção de uma palavra na árvore TST
void tst_insert(TST *root, char *str, benchmark_t* b) {
  insert(root, str, 0, strlen(str), b);
}

static int search(TST *root, char *str, int pos, int len, benchmark_t* b) {
  benchmark_sum_qtd_comp(b, 1);
  if ((*root) == NULL) {
    return 0;
  }
  benchmark_sum_qtd_comp(b, 2);
  if (pos == len && (*root)->end_word == 1) {
    return 1;
  }

  if (str[pos] == (*root)->character) {
    benchmark_sum_qtd_comp(b, 1);
    return search(&(*root)->middle, str, pos+1, len, b);
  } else if (str[pos] > (*root)->character) {
    benchmark_sum_qtd_comp(b, 2);
    return search(&(*root)->right, str, pos, len, b);
  } else {
    benchmark_sum_qtd_comp(b, 2);
    return search(&(*root)->left, str, pos, len, b);
  }
}

//Operação de pesquisa de uma palavra na árvore TST
int tst_search(TST *root, char *str, benchmark_t* b) {
  return search(root, str, 0, strlen(str), b);
}

void print_tst(TST root, char* word, int pos) {
  if (root == NULL) {
    pos=0;
    return;
  }

  print_tst(root->left, word, pos);

  strncat(word, &root->character, sizeof(char));
  if(root->end_word) puts(word);
  
  print_tst(root->middle, word, pos+1);
  word[pos] = '\0';

  print_tst(root->right, word, pos); 
}

//Operação para imprimir em ordem em uma árvore TST
void tst_print(TST root) {
  char word[256];
  strcpy(word, "");

  print_tst(root, word, 0);
}

static int word_countT(TST root, int count) {
  if (root == NULL) return count;

  count = word_countT(root->left, count);
 
  if(root->end_word) count++;
 
  count = word_countT(root->middle, count);

  count = word_countT(root->right, count); 
  
}

void tst_remove_nodes(TST *root) {
  if ((*root) == NULL) return;
  tst_remove_nodes(&(*root)->left);
  tst_remove_nodes(&(*root)->middle);
  tst_remove_nodes(&(*root)->right);
  free((*root));
  *root=NULL;
}

//Operação para contar o número de palavras em uma árvore TST
int tst_word_count (TST root) {
  return word_countT(root, 0);
}

static int tst_count_nodes(TST root) {
  if (root == NULL) return 0;

  return 1 + tst_count_nodes(root->left) + 
          tst_count_nodes(root->middle) + 
          tst_count_nodes(root->right); 
}

void tst_mem_size(TST tst, benchmark_t *b) {
  b->mem_insertion = sizeof(struct node_t)*tst_count_nodes(tst);
}
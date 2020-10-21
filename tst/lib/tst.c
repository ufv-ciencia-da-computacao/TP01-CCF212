//Grupo Raiz
#include "tst.h"

void tst_node_init(TST *root, char ch) {
  (*root) = (TST) malloc(sizeof(struct node_t));

  (*root)->left = NULL;
  (*root)->middle = NULL;
  (*root)->right = NULL;
  (*root)->end_word = 0;
  (*root)->character = ch;
}

static void insert(TST *root, char* str, int pos, int len, int* qtdComp) {
  (*qtdComp)++;
  if ((*root) == NULL) {
      tst_node_init(root, str[pos]);
    }

  (*qtdComp)++;
  if (pos == len) {
    (*root)->end_word = 1;
    return;
  }

  if (str[pos] == (*root)->character) {
    (*qtdComp)++;
    insert(&(*root)->middle, str, pos+1, len, qtdComp);
  } else if (str[pos] > (*root)->character) {
    (*qtdComp) += 2;
    insert(&(*root)->right, str, pos, len, qtdComp);
  } else {
    (*qtdComp) += 2;
    insert(&(*root)->left, str, pos, len, qtdComp);
  }
  
}

//Operação de inserção de uma palavra na árvore TST
void tst_insert(TST *root, char *str, int* qtdComp) {
  *qtdComp = 0;
  insert(root, str, 0, strlen(str), qtdComp);
}

static int search(TST *root, char *str, int pos, int len, int* qtdComp) {
  (*qtdComp)++;
  if ((*root) == NULL) {
    return 0;
  }
  (*qtdComp) += 2;
  if (pos == len && (*root)->end_word == 1) {
    return 1;
  }

  if (str[pos] == (*root)->character) {
    (*qtdComp)++;
    return search(&(*root)->middle, str, pos+1, len, qtdComp);
  } else if (str[pos] > (*root)->character) {
    (*qtdComp) += 2;
    return search(&(*root)->right, str, pos, len, qtdComp);
  } else {
    (*qtdComp) += 2;
    return search(&(*root)->left, str, pos, len, qtdComp);
  }
}

//Operação de pesquisa de uma palavra na árvore TST
int tst_search(TST *root, char *str, int* qtdComp) {
  *qtdComp = 0;
  return search(root, str, 0, strlen(str), qtdComp);
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

//Operação para contar o número de palavras em uma árvore TST
int tst_word_count (TST root) {
  return word_countT(root, 0);
}
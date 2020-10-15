#include "tst.h"

void tst_node_init(TST *root, char ch) {
  (*root) = (TST) malloc(sizeof(struct node_t));

  (*root)->left = NULL;
  (*root)->middle = NULL;
  (*root)->right = NULL;
  (*root)->end_word = 0;
  (*root)->character = ch;
}

static void insert(TST *root, char* str, int pos, int len) {
  if ((*root) == NULL) tst_node_init(root, str[pos]);

  if (pos == len) {
    (*root)->end_word = 1;
    return;
  }

  if (str[pos] == (*root)->character) insert(&(*root)->middle, str, pos+1, len);
  else if (str[pos] > (*root)->character) insert(&(*root)->right, str, pos, len);
  else insert(&(*root)->left, str, pos, len);
  
}

void tst_insert(TST *root, char *str) {
  insert(root, str, 0, strlen(str));
}

static int search(TST *root, char *str, int pos, int len) {
  if ((*root) == NULL) return 0;
  if (pos == len) return 1;

  if (str[pos] == (*root)->character) return search(&(*root)->middle, str, pos+1, len);
  else if (str[pos] > (*root)->character) return search(&(*root)->right, str, pos, len);
  else return search(&(*root)->left, str, pos, len);
}

int tst_search(TST *root, char *str) {
  return search(root, str, 0, strlen(str));
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

void tst_print(TST root) {
  char word[256];
  strcpy(word, "");

  print_tst(root, word, 0);
}

static int word_count(TST root, int count) {
  if (root == NULL) return count;

  count = word_count(root->left, count);
 
  if(root->end_word) count++;
 
  count = word_count(root->middle, count);

  count = word_count(root->right, count); 
  
}

int tst_word_count (TST root) {
  return word_count(root, 0);
}
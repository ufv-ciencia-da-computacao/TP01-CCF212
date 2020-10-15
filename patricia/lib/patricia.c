#include "patricia.h"

typedef struct {
  int index;
  char character;
} tuple_t;

int min(int a, int b) {
  return (a < b ? a : b);
}

tuple_t get_char(Item a, Item b) {
  size_t item_a = strlen(a);
  size_t item_b = strlen(b);

  tuple_t tuple;

  int m = min(item_a, item_b);

  for(int i=0; i<m; i++) {
    if (a[i] == '\0') {
      tuple.character = a[i];
      tuple.index = i;
      return tuple;
    } else if(b[i] == '\0') {
      tuple.character = b[i];
      tuple.index = i;
      return tuple;
    }
    else if (a[i] != b[i]) {
      if (a[i] <= b[i]) tuple.character = a[i];
      else tuple.character = b[i];
      
      tuple.index = i;
      return tuple;
    }
  }
}

int type_node(Patricia p) {
  return (p->type == external);
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

int pat_search(Patricia patricia, Item key) {
  if (type_node(patricia) == external) {
    return strcmp(key, patricia->node.key) == 0 ? 1:0;
  } 


  printf("%d", patricia->node.node_internal.index);
  printf("%c\n", patricia->node.node_internal.character);

  if (key[patricia->node.node_internal.index] <= patricia->node.node_internal.character) 
    return pat_search(patricia->node.node_internal.left, key);
  else return pat_search(patricia->node.node_internal.right, key);
}

void pat_print(Patricia patricia) {
  if (patricia == NULL) return;
  
  if (type_node(patricia) == internal) pat_print(patricia->node.node_internal.left);
  if (type_node(patricia) == external) puts(patricia->node.key); 
  if (type_node(patricia) == internal) pat_print(patricia->node.node_internal.right);
}

static int word_count(Patricia patricia, int count) {
  if (patricia == NULL) return count;
  
  if (type_node(patricia) == internal) count = word_count(patricia->node.node_internal.left, count);
  if (type_node(patricia) == external) return count+1;
  if (type_node(patricia) == internal) count = word_count(patricia->node.node_internal.right, count);
}

int pat_word_count (Patricia patricia) {
  return word_count(patricia, 0);
}

Patricia pat_insert_node_internal(Patricia* patricia, Item key, tuple_t tuple) {
  Patricia new;
  if (type_node(*patricia) == external || tuple.index < (*patricia)->node.node_internal.index) {
    pat_init_external(&new, key);
    if (key[tuple.index] > tuple.character) {
      return pat_init_internal(patricia, &new, tuple);
    } else {
      return pat_init_internal(&new, patricia, tuple);
    }
  } else {
    if (key[(*patricia)->node.node_internal.index] >  (*patricia)->node.node_internal.character) {
      (*patricia)->node.node_internal.right = 
              pat_insert_node_internal(&(*patricia)->node.node_internal.right, key, tuple);
    } else {
      (*patricia)->node.node_internal.left = 
              pat_insert_node_internal(&(*patricia)->node.node_internal.left, key, tuple);
    }
    return (*patricia);
  }
}

Patricia pat_insert(Patricia* patricia, Item key) {
  if((*patricia) == NULL) {
    pat_init_external(patricia, key);
    return (*patricia);
  } 
  
  Patricia aux = *patricia;

  while (type_node(aux) != external) {
    if (key[aux->node.node_internal.index] > aux->node.node_internal.character) {
      aux = aux->node.node_internal.right;
    } else aux = aux->node.node_internal.left;
  }

  tuple_t tuple = get_char(key, aux->node.key);

  return pat_insert_node_internal(patricia, key, tuple);  
}
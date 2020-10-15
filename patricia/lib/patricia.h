#ifndef __PATRICIA_H__
#define __PATRICIA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define D 8 // Depends on type of Item
#define CHARACTERS 256


typedef char Item[CHARACTERS];
typedef int index_amp;

typedef enum {
  internal, external
} node_type;

typedef struct pat_node_str* Patricia;
typedef struct pat_node_str {
  node_type type;
  union {
    struct {
      char character;
      index_amp index;
      Patricia left;
      Patricia right;
    }node_internal;
    Item key;
  }node;
} pat_node;

int type_node(Patricia p);
void pat_init(Patricia* patricia);
void pat_print(Patricia patricia);
int pat_word_count (Patricia patricia);
int pat_search(Patricia patricia, Item key);
Patricia pat_insert(Patricia* patricia, Item key);
#endif
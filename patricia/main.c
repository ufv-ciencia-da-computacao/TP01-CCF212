#include <stdio.h>
#include <stdlib.h>
#include "./lib/patricia.h"

int main () {
  char strings[9][256] = {"parade", "party", "parties", "participation", "participle", "park", "parking", "zebra", "giraffe"};
  Patricia patricia=NULL;
  
  int i=0;
  for (i=0; i<9; i++) {
    patricia = pat_insert(&patricia, strings[i]);
  }

  // printf(pat_search(patricia, "participle") ? "YES\n":"NO\n");
  // printf(pat_search(patricia, "parking") ? "YES\n":"NO\n");
  // printf(pat_search(patricia, "D") ? "YES\n":"NO\n");

  pat_print(patricia);
  printf("Numero de palavras: %d\n", pat_word_count(patricia));

  return 0;
}

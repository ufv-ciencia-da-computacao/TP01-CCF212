//Grupo Raiz
#include <stdio.h>
#include <stdlib.h>
#include "./lib/tst.h"

int main () {
  char strings[9][256] = {"parade", "party", "parties", "participation", "participle", "park", "parking", "zebra", "giraffe"};
  TST tst=NULL;

  int i=0;
  for (i=0; i<9; i++) {
    tst_insert(&tst, strings[i]);
  }

  // printf(tst_search(&tst, "visible") ? "YES\n":"NO\n");
  // printf(tst_search(&tst, "charm") ? "YES\n":"NO\n");
  // printf(tst_search(&tst, "germano") ? "YES\n":"NO\n");

  tst_print(tst);

  printf("%d\n", tst_word_count(tst));
  return 0;
}

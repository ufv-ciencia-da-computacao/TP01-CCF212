#include <stdio.h>
#include <stdlib.h>
#include "./lib/patricia.h"

int main () {
  char strings[7][256] = {"parade", "party", "parties", "paticipation", "paticiple", "park", "parking"};
  Patricia patricia=NULL;

  int i=0;
  for (i=0; i<7; i++) {
    patricia = pat_insert(&patricia, strings[i]);
  }

  printf(pat_search(patricia, "party") ? "YES\n":"NO\n");
  printf(pat_search(patricia, "parkin") ? "YES\n":"NO\n");
  printf(pat_search(patricia, "D") ? "YES\n":"NO\n");

  return 0;
}

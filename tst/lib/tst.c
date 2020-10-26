//Grupo Raiz
#include "tst.h"
#include "../../benchmark/lib/benchmark.h"

//Operação de inicialização de novo nó para árvore Trie TST
void tst_node_init(TST *root, char ch) {
  (*root) = (TST) malloc(sizeof(struct node_t));

  (*root)->left = NULL;
  (*root)->middle = NULL;
  (*root)->right = NULL;
  (*root)->end_word = 0;
  (*root)->character = ch;
}

//Operação interna de inserção
static void insert(TST *root, char* str, int pos, int len, benchmark_t *b) {
  benchmark_sum_qtd_comp(b, 1); //chamada para contagem de comparações
  if ((*root) == NULL) {
    tst_node_init(root, str[pos]); //Caso base: árvore vazia ou posição com nó nulo, inicia um novo nó
  }

  /*Enquanto não chega ao fim da palavra, chama-se recursivamente para o meio,
  para a direita ou para esqueda até que todos os caracteres sejam inseridos
  na posição correta*/
  if (str[pos] > (*root)->character) {
    benchmark_sum_qtd_comp(b, 1);
    insert(&(*root)->right, str, pos, len, b);
  } else if (str[pos] < (*root)->character) {
    benchmark_sum_qtd_comp(b, 2);
    insert(&(*root)->left, str, pos, len, b);
  } else {
    benchmark_sum_qtd_comp(b, 3);
    if (pos == (len-1)) {
      (*root)->end_word = 1; //Se chegar ao final da palavra, muda o flag 'end_word' para 1
    } else {
      insert(&(*root)->middle, str, pos+1, len, b);
    }
  }
  
}

//Operação de inserção de uma palavra na árvore TST
void tst_insert(TST *root, char *str, benchmark_t* b) {
  insert(root, str, 0, strlen(str), b);
}

//Operação interna de pesquisa
static int search(TST *root, char *str, int pos, int len, benchmark_t* b) {
  benchmark_sum_qtd_comp(b, 1); //chamada para contagem de comparações
  if ((*root) == NULL) {
    return 0; //Caso base (Palavra não está na árvore ou árvore vazia)
  }

  /*Testa se o caracter da palavra procurada é igual, menor ou maior
  que a chave atual e faz a chamada recursiva de acordo com a resposta:
  pelo meio caso seja igual, direita se maior, esquerda se menor*/
  if (str[pos] < (*root)->character) {
    benchmark_sum_qtd_comp(b, 1);
    return search(&(*root)->left, str, pos, len, b);
  } else if (str[pos] > (*root)->character) {
    benchmark_sum_qtd_comp(b, 2);
    return search(&(*root)->right, str, pos, len, b);
  } else {
    benchmark_sum_qtd_comp(b, 4);
    if (pos == len-1 && (*root)->end_word == 1) {
      return 1; //Retorno caso a palavra procurada seja encontrada
    }
    return search(&(*root)->middle, str, pos+1, len, b);
  }
}

//Operação de pesquisa de uma palavra na árvore TST
int tst_search(TST *root, char *str, benchmark_t* b) {
  return search(root, str, 0, strlen(str), b);
}

//Operação interna para impressão em ordem
void print_tst(TST root, char* word, int pos) {
  if (root == NULL) {
    return;
  }

  print_tst(root->left, word, pos);

  word[pos] = root->character; //armazena em 'word' o caracter atual
  if(root->end_word) { 
    word[pos+1] = '\0';
    puts(word); //imprime a palavra salva em 'word' sempre que encontra um fim de palavra (end_word==1)
  }
  print_tst(root->middle, word, pos+1);
  print_tst(root->right, word, pos); 
}

//Operação para imprimir em ordem uma árvore TST
void tst_print(TST root) {
  char word[256];
  strcpy(word, "");

  print_tst(root, word, 0);
}

//Operação interna para contagem do número de palavras em uma árvore Trie TST (Faz um percurso em ordem)
static int word_countT(TST root, int count) {
  if (root == NULL) return count;
  
  count = word_countT(root->left, count);
 
  if(root->end_word) count++; //Soma-se 1 sempre que encontra o final de uma palavra, ou seja, quando end_word é igual a 1
 
  count = word_countT(root->middle, count);
  count = word_countT(root->right, count);  
}

//Operação para contar o número de palavras em uma árvore TST
int tst_word_count (TST root) {
  return word_countT(root, 0);
}

//Operação para desalocar árvore Trie TST
void tst_remove_nodes(TST *root) {
  if ((*root) == NULL) return;
  tst_remove_nodes(&(*root)->left); //utiliza-se a ideia de desalocar todos os nós filhos e posteriormente o nó raiz (pós ordem)
  tst_remove_nodes(&(*root)->middle);
  tst_remove_nodes(&(*root)->right);
  free((*root));
  *root=NULL;
}

//Operação para contar número total de nós em uma árvore
static int tst_count_nodes(TST root) {
  if (root == NULL) return 0;

  return 1 + tst_count_nodes(root->left) + 
          tst_count_nodes(root->middle) + 
          tst_count_nodes(root->right); 
}

//Operação para verificar espaço alocado para árvore
void tst_mem_size(TST tst, benchmark_t *b) {
  //Chama a função que conta os nós para saber a quantidade de total de memória alocada
  b->mem_insertion = sizeof(struct node_t)*tst_count_nodes(tst);
}
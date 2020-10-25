//Grupo Raiz
#include "patricia.h"
#include "../../benchmark/lib/benchmark.c"

typedef struct {
  int index;
  char character;
} tuple_t;

//Operação que retorna o menor valor entre dois valores a e b
int min(int a, int b) {
  return (a < b ? a : b);
}

//Operação interna que retorna o caractere que será armazenado em um nó interno 
tuple_t get_char(String a, String b, benchmark_t* bench) {
  size_t item_a = strlen(a);
  size_t item_b = strlen(b);

  tuple_t tuple;

  int m = min(item_a, item_b);

  /*percorre a palavra até encontrar o caratere em que se diferem,
  ao encontrar escolhe o menor caractere entre os dois ou o \0 e 
  retorna a posição em que se encontram e também o caractere, como tuple*/
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

//Operação que retorna o tipo do nó, interno(0) ou externo(1)
int type_node(Patricia p) {
  return (p->type);
}

//Operação interna para inicialização de um novo nó interno 
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

//Operação interna para inicialização de um novo nó externo
void pat_init_external(Patricia *patricia, String key) {
  (*patricia) = (Patricia) malloc(sizeof(pat_node));
  (*patricia)->type = external;
  (*patricia)->node.key = (String) malloc((strlen(key)+1)*sizeof(char)); //aloca espaço para inserção da nova palavra
  strcpy((*patricia)->node.key, key);
}

//Operação de pesquisa em uma árvore Patricia
int pat_search(Patricia patricia, String key, benchmark_t* b) {
  benchmark_sum_qtd_comp(b, 1);
  if (type_node(patricia) == external) { //Caso base: Quando as chamadas recursivas chegam a um nó externo
    benchmark_sum_qtd_comp(b, 1);
    return strcmp(key, patricia->node.key) == 0 ? 1:0; //Retorna 1 se a palavra procurada for igual a palavra salva no nó externo atual
  }

  /*Executa as comparações dos nós internos com a palavra procurada, chamando recursivamente
  a operação para a esquerda se a palavra tiver um caracter menor que o comparado ou para 
  a direita caso contrário*/
  if (key[patricia->node.node_internal.index] <= patricia->node.node_internal.character)  {
    benchmark_sum_qtd_comp(b, 1);
    return pat_search(patricia->node.node_internal.left, key, b);
  } else {
    benchmark_sum_qtd_comp(b, 1);
    return pat_search(patricia->node.node_internal.right, key, b);
  }
}

//Operação que imprime uma árvore Patricia em Ordem
void pat_print(Patricia patricia) {
  if (patricia == NULL) return;
  
  //Faz um percurso em ordem: vai primeiro nos nós a esquerda e depois nos nós a direita recursivamente
  if (type_node(patricia) == internal) pat_print(patricia->node.node_internal.left);
  if (type_node(patricia) == external) puts(patricia->node.key); //Imprime apenas quando se encontra um nó externo
  if (type_node(patricia) == internal) pat_print(patricia->node.node_internal.right);
}

//Operação interna que conta o número de palavras
int word_countP(Patricia patricia, int count) {
  if (patricia == NULL) return count;
  
  //Percorre a árvore em ordem recursivamente e soma um sempre que encontra um nó externo
  if (type_node(patricia) == internal) count = word_countP(patricia->node.node_internal.left, count);
  if (type_node(patricia) == external) return count+1;
  if (type_node(patricia) == internal) count = word_countP(patricia->node.node_internal.right, count);
}

//Operação que conta o número de palavras de uma árvore Patricia
int pat_word_count(Patricia patricia) {
  return word_countP(patricia, 0);
}

//Operação interna para inserção de novo nó interno
Patricia pat_insert_node_internal(Patricia* patricia, String key, tuple_t tuple, benchmark_t* b) {
  Patricia new;
  //Se o nó atual for um nó externo ou se a palavra for menor que o indice do interno atual
  if (type_node(*patricia) == external || tuple.index < (*patricia)->node.node_internal.index) {
    benchmark_sum_qtd_comp(b, 2);
    pat_init_external(&new, key); //Cria nó externo para armazer palavra
    //escolhe se a string será inserida a esquerda ou a direita do novo nó interno
    if (key[tuple.index] > tuple.character) {
      benchmark_sum_qtd_comp(b, 1);
      return pat_init_internal(patricia, &new, tuple);
    } else {
      benchmark_sum_qtd_comp(b, 1);
      return pat_init_internal(&new, patricia, tuple);
    }
  } else {
    /*Caso contrário, compara-se até que encontre a posição onde será inserida a palavra
    comparando sempre se será inserida a esquerda ou a direita do nó atual
    e chamando recursivamente a função*/
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
    return (*patricia); // retorna Patricia com nova palavra
  }
}

//Operação para inserção de uma nova palavra em uma árvore Patricia
Patricia pat_insert(Patricia* patricia, String key, benchmark_t* b) {

  benchmark_sum_qtd_comp(b, 1);
  if((*patricia) == NULL) {
    pat_init_external(patricia, key); //Caso base: árvore vazia, inicia novo nó externo e armazena a palavra nele
    return (*patricia);
  } 
  
  Patricia aux = *patricia;

  /*Enquanto não é encontrado um nó externo, percorre-se a ávore comparando
  a palavra em determinado índice com o caracter salvo naquele nó interno,
  chamando a operação recursivamente para a direita caso o caracter possua
  um valor maior, ou para a esquerda caso possua um valor menor que o comparado*/
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

  return pat_insert_node_internal(patricia, key, tuple, b); //Chama operação para criação de nó interno e armazenar palavra
}

//Operação para medição de memória alocada por uma Patricia
void pat_mem_size(Patricia pat, benchmark_t *b) {
  if (pat == NULL) return;
  
  /*Como o espaço alocado para nós internos e externos é diferente, precisamos
  checar para que possamos medir adequadamente a memória alocada por eles*/
  if (type_node(pat) == external) {
    benchmark_sum_mem_insertion(b, strlen(pat->node.key)*sizeof(char) + sizeof(pat_node));
    return;
  }

  benchmark_sum_mem_insertion(b, sizeof(pat_node));
  pat_mem_size(pat->node.node_internal.left, b);
  pat_mem_size(pat->node.node_internal.right, b);
}

//Operação para desalocar árvore Patricia
void pat_remove_nodes(Patricia *pat) {
  if((*pat)==NULL) return; //Caso base: árvore totalmente vazia

  //Se for um nó externo desaloca-o
  if (type_node((*pat)) == external) {
    free((*pat)->node.key);
    free((*pat));
    *pat=NULL;
    return;
  }

  pat_remove_nodes(&(*pat)->node.node_internal.left); //Chamada recursiva para nós a esquerda
  pat_remove_nodes(&(*pat)->node.node_internal.right); //Chamada recursiva para nós a direita
  free((*pat)); //Desaloca nó interno
  *pat=NULL;
} 
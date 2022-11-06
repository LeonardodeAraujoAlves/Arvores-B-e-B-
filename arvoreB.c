#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct NoArvoreB {
  int val[MAX + 1], contador;
  struct NoArvoreB *link[MAX + 1];
};

struct NoArvoreB *raiz;


struct NoArvoreB *CriaNo(int val, struct NoArvoreB *filho) {
  struct NoArvoreB *NovoNo;
  NovoNo = (struct NoArvoreB *)malloc(sizeof(struct NoArvoreB));
  NovoNo->val[1] = val;
  NovoNo->contador = 1;
  NovoNo->link[0] = raiz;
  NovoNo->link[1] = filho;
  return NovoNo;
}

void inseritNo(int val, int pos, struct NoArvoreB *node,struct NoArvoreB *filho);
void dividirNo(int val, int *pval, int pos, struct NoArvoreB *node,struct NoArvoreB *filho, struct NoArvoreB **NovoNo);
int definirValor(int val, int *pval,struct NoArvoreB *node, struct NoArvoreB **filho);
void inserir(int val);
void buscar(int val, int *pos, struct NoArvoreB *myNode);
void percorre(struct NoArvoreB *myNode); 

int main() {
  int val, ch;

  inserir(1);
  inserir(2);
  inserir(54);
  inserir(46);
  inserir(18);
  inserir(20);
  inserir(14);
  inserir(15);
 

 percorre(raiz);

  printf("\n");
  buscar(51, &ch, raiz);
}

// Insert node
void inseritNo(int val, int pos, struct NoArvoreB *node,struct NoArvoreB *filho) {
  int j = node->contador;
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = filho;
  node->contador++;
}


void dividirNo(int val, int *pval, int pos, struct NoArvoreB *node,struct NoArvoreB *filho, struct NoArvoreB **NovoNo) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *NovoNo = (struct NoArvoreB *)malloc(sizeof(struct NoArvoreB));
  j = median + 1;
  while (j <= MAX) {
    (*NovoNo)->val[j - median] = node->val[j];
    (*NovoNo)->link[j - median] = node->link[j];
    j++;
  }
  node->contador = median;
  (*NovoNo)->contador = MAX - median;

  if (pos <= MIN) {
    inseritNo(val, pos, node, filho);
  } else {
    inseritNo(val, pos - median, *NovoNo, filho);
  }
  *pval = node->val[node->contador];
  (*NovoNo)->link[0] = node->link[node->contador];
  node->contador--;
}


int definirValor(int val, int *pval,
           struct NoArvoreB *node, struct NoArvoreB **filho) {
  int pos;
  if (!node) {
    *pval = val;
    *filho = NULL;
    return 1;
  }

  if (val < node->val[1]) {
    pos = 0;
  } else {
    for (pos = node->contador;
       (val < node->val[pos] && pos > 1); pos--)
      ;
    if (val == node->val[pos]) {
      printf("Valores duplicados nao sao permitidos\n");
      return 0;
    }
  }
  if (definirValor(val, pval, node->link[pos], filho)) {
    if (node->contador < MAX) {
      inseritNo(*pval, pos, node, *filho);
    } else {
      dividirNo(*pval, pval, pos, node, *filho, filho);
      return 1;
    }
  }
  return 0;
}


void inserir(int val) {
  int flag, i;
  struct NoArvoreB *filho;

  flag = definirValor(val, &i, raiz, &filho);
  if (flag)
    raiz = CriaNo(i, filho);
}


void buscar(int val, int *pos, struct NoArvoreB *myNode) {
  if (!myNode) {
    return;
  }

  if (val < myNode->val[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->contador;
       (val < myNode->val[*pos] && *pos > 1); (*pos)--)
      ;
    if (val == myNode->val[*pos]) {
      printf("%d Valor encontrado", val);
      return;
    }else{
    	printf("%d Valor nao encontrado",val);
    	return;
	}
  }
  buscar(val, pos, myNode->link[*pos]);

  return;
}


void percorre(struct NoArvoreB *myNode) {
  int i;
  if (myNode) {
    for (i = 0; i < myNode->contador; i++) {
      percorre(myNode->link[i]);
      printf("%d \n", myNode->val[i + 1]);
    }
    percorre(myNode->link[i]);
  }
}


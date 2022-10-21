#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
  Aluno *aluno;
  struct node *proximo;
};

typedef struct node No;

struct fila {
  No *primeiro, *fim;
};

/* Aloca espaço em memória e retorna uma fila */
Fila *fila_cria() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->primeiro = NULL;
  return fila;
  /*Aloca espaço na memória, atribui NULL ao primeiro da fila e retorna ela*/
}

/* Libera a memória de uma fila previamente criada e atribui NULL ao ponteiro
 * fila. Retorna 1 caso seja possível fazer a liberação e 0 caso a fila
 * informada seja NULL. */
int fila_libera(Fila **fila) {
  if (fila != NULL) {
  /*Se fila não for NULL, então:*/
    if ((*fila)->primeiro != NULL) {
      No *auxiliar = (*fila)->primeiro;
    /*Se o primeiro da fila não for NULL, armazena o primeiro no Nó auxiliar e então:*/
      do {
        alu_libera(&auxiliar->aluno);
        auxiliar = auxiliar->proximo;
      }
      /*Libera a memória do Nó auxiliar e depois atribui o próximo da fila ao auxiliar*/

      while (auxiliar != NULL);
      /*Fara isso até que auxilar seja NULL, ou seja até toda a fila seja liberada*/
    }
    free(*fila);
    *fila = NULL;
    return 1;
    /*Libera a fila, atribui NULL e retorna 1*/
  }
  return 0;
  /*Retorna 0 se a fila for NULL*/
}

/* Insere um aluno na fila. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a fila ou aluno sejam NULL
 */
int fila_insere(Fila *fila, Aluno *aluno) {
  if (aluno == NULL || fila == NULL) {
    return -1;
  }
  /*Se a fila ou aluno for NULL retorna -1*/

  int matricula;
  char nome[50];
  char curso[30];
  /*Declara localmente as variáveis*/

  alu_acessa(aluno, &matricula, nome, curso);
  /*Chama a função alu_acessa para acessar e armazenar os dados*/

  Aluno *alu;
  alu = fila_busca(fila, matricula);
  /*Buscar aluno pela matrícula e atribuir a variável alu*/

  if (alu != NULL) {
    return 0;
  }
  /*Se já existir a matricula, retorna 0*/
  /*Neste momento eu sei que a fila ou aluno não são NULL e que não existe aluno*/

  No *novo_aluno = (No *)malloc(sizeof(No));
  novo_aluno->aluno = aluno;
  novo_aluno->proximo = NULL;
  /*Faz um novo nó e aloca espaço na memória. Atribui ao novo_aluno o aluno a ser inserido e NULL ao próximo da fila*/

  No *auxiliar = fila->primeiro;
  /*Cria um Node auxiliar que contem o primeiro da fila*/

  if (auxiliar == NULL) {
    fila->primeiro = novo_aluno;
    return 1;
  }
  /*Se o primeiro da fila for igual a NULL, então atribui o novo_aluno no primeiro lugar da fila e retorna 1*/

  for (;auxiliar != NULL; auxiliar = auxiliar->proximo) {
  /*Percorre a lista encadeada enquanto o "próximo" é NULL e adiciona o novo aluno*/
    if (auxiliar->proximo == NULL) {
      auxiliar->proximo = novo_aluno;
      return 1;
    }
    /*Se próximo é NULL, então insere*/
  }
}

/* Remove um aluno na fila. Retorna o aluno ou NULL caso a fila esteja vazia ou
 * seja NULL */
Aluno *fila_retira(Fila *fila) {
  if (fila == NULL) {
    return NULL;
  }
  /*Se a fila for NULL, retorna NULL*/

  No *primeiro = fila->primeiro;
  No *segundo = primeiro->proximo;
  /*O nó primeiro, recebe o primeiro da fila e o segundo, recebe o próximo da primeiro*/

  fila->primeiro = segundo;
  return primeiro->aluno;
  /*Sobrescreve o primeiro aluno, com o segundo aluno e retorna*/
}

/* Recupera o primeiro aluno da fila. Retorna o aluno ou NULL caso a fila esteja
 * vazia ou seja NULL */
Aluno *fila_primeiro(Fila *fila) {
  if (fila == NULL || fila->primeiro == NULL) {
    return NULL;
  }
  /*Se a fila ou o primeiro aluno for NULL, retorna NULL*/
  return fila->primeiro->aluno;
}
  /*Do contrário, retorna o primeiro aluno da fila*/

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) fila vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a fila seja NULL */
Aluno *fila_busca(Fila *fila, int matricula) {
  if (fila == NULL ) {
    return NULL;
  }
  /*Se a fila for NULL, retorna NULL*/

  int matricula_auxiliar;
  char nome[50];
  char curso[30];
  /*Declara variáveis locais*/

  for (No *no_auxiliar = fila->primeiro; no_auxiliar != NULL; no_auxiliar = no_auxiliar->proximo){
  /*Percorre a lista encadeada enquanto o próximo é NULL*/

    alu_acessa(no_auxiliar->aluno, &matricula_auxiliar, nome, curso);
    /*Usa a função alu_acessa() para armazenar no no_auxiliar os alunos da lista*/

    if (matricula_auxiliar == matricula) {
      return no_auxiliar->aluno;
    }
    /*Se a matrícula estiver na lista, retorna o aluno correspondente*/
  }

  return NULL;
  /*Já verificado se a fila é NULL ou contém o aluno buscado, se não for validado, retorna NULL por a fila ser vazia ou*/
  /*por a matrícula não estar presente na lista.*/
}

/* Verifica se a fila está vazia. Retorna 1 se a fila estiver vazia, 0 caso não
 * esteja vazia e -1 se a fila for NULL
 */
int fila_vazia(Fila *fila) {
  if (fila == NULL) {
    return -1;
  }
  /*Se fila NULL, retorna -1*/
  else if (fila->primeiro == NULL) {
    return 1;
  }
  /*Se o primeiro da fila for NULL, a fila está vazia e retorna 1*/
  else if (fila->primeiro != NULL) {
    return 0;
  }
  /*Se for diferente de NULL, a fila não está vazia e retorna 0*/
}

/* Computa a quantidade de alunos alunos na fila. Retorna a quantidade de alunos
 * ou -1, caso a fila for NULL.
 */
int fila_quantidade(Fila *fila) {
  if (fila == NULL) {
    return -1;
  }
  /*Se a fila é NULL, retorna -1*/
  int quantidade = 0;
  for (No *no_auxiliar = fila->primeiro; no_auxiliar != NULL; no_auxiliar = no_auxiliar->proximo){
      quantidade ++;
  }
  return quantidade;
  /*Do contrário, retorna o tamanho da fila*/
}
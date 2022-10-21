#include "Fila.h"
#include "Aluno.h"
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_INICIAL 10

struct fila {
  int tamanho;
  int capacidade_maxima;
  Aluno *fila_alunos;
};

/* Aloca espaço em memória e retorna uma fila */
Fila *fila_cria() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->fila_alunos = (Aluno *)malloc(CAPACIDADE_INICIAL * sizeof(Aluno *));
  fila->capacidade_maxima = CAPACIDADE_INICIAL;
  fila->tamanho = 0;
  return fila;
}

/* Libera a memória de uma fila previamente criada e atribui NULL ao ponteiro
 * fila. Retorna 1 caso seja possível fazer a liberação e 0 caso a fila
 * informada seja NULL. */
int fila_libera(Fila **fila) {
  if (fila != NULL) {
  /*Se a fila for diferente de NULL*/
    if ((*fila)->tamanho > 0) {
    /*Se a fila não está vazia*/
      free((*fila)->fila_alunos);
      (*fila)->fila_alunos = NULL;
    /*Libera a memória e atribui NULL a fila*/
    }
    free(*fila);
    *fila = NULL;
    return 1;
    /*Libera memória, atribui NULL a fila e retorna 1*/
  }
  return 0;
  /*Se a fila for NULL, retorna 0*/
}

/* Insere um aluno na fila. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a fila ou aluno sejam NULL
 */
int fila_insere(Fila *fila, Aluno *aluno) {
    /*IF para verificar se a fila ou aluno é NULL*/
    if(fila == NULL || aluno == NULL) {
        return -1;
    }
    /*Neste momento eu sei que a fila e aluno não são NULL*/
    if(fila_busca(fila, pegamatricula(aluno)) != NULL){
        return 0;
    }
    /*Caso a matrícula já exista na fila, o IF é validado e retorna 0*/
    (&(fila->fila_alunos))[fila->tamanho] = aluno;
    fila->tamanho = fila->tamanho + 1;
    return 1;
    /*Do contrário, o aluno é inserido e retorna 1*/
}

/* Remove um aluno na fila. Retorna o aluno ou NULL caso a fila esteja vazia ou
 * seja NULL */
Aluno *fila_retira(Fila *fila) {
    /*If para verificar se a fila está vazia ou é NULL*/
    if (fila == NULL || fila->tamanho == 0){
        return NULL;
    }
    Aluno *aluno = (&(fila->fila_alunos))[0];
    /*For para remover o aluno na fila*/
    for(int i = 1; i < fila->tamanho; i++){
        (&(fila->fila_alunos))[i-1] = (&(fila->fila_alunos))[i];
    }
    /*Atribui NULL ao último "Aluno" da fila(?)*/
    (&(fila->fila_alunos))[fila->tamanho - 1] = NULL;
    return aluno;
}

/* Recupera o primeiro aluno da fila. Retorna o aluno ou NULL caso a fila esteja
 * vazia ou seja NULL */
Aluno *fila_primeiro(Fila *fila) {
  if (fila == NULL || fila->tamanho == 0) {
    return NULL;
    /*Se fila vazia ou NULL, retorna NULL*/
  }
  return (&(fila->fila_alunos))[0];
  /*Do contrario, retorna o aluno na posição 0*/
}

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) fila vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a fila seja NULL */
Aluno *fila_busca(Fila *fila, int matricula) {
    if(fila == NULL || fila->tamanho == 0){
        return NULL;
    }
    /*Se a fila for NULL ou estiver vazia, retorna NULL*/

    for(int i = 0; i < fila->tamanho; i++){
        /*FOR para percorrer a fila com o seu tamanho de parametro*/
        Aluno *aluno = (&(fila->fila_alunos))[i];
        /*aluno vai receber as informações do aluno na posição i*/
        if (pegamatricula(aluno) == matricula){
            return aluno;
        /*Se a matricula estiver presente, retorna esse aluno*/
        }
    }
    return NULL;
    /*Do contrario, retorna NULL*/
}

/* Verifica se a fila está vazia. Retorna 1 se a fila estiver vazia, 0 caso não
 * esteja vazia e -1 se a fila for NULL
 */
int fila_vazia(Fila *fila) {
  if (fila == NULL) {
    return -1;
  }
  /*Se fila NULL, retorna -1*/

  if (fila->tamanho == 0) {
    return 1;
  }
  /*Se fila vazia, retorna 1*/

  return 0;
  /*Caso nenhum IF seja validado, a fila não está NULL e nem Vazia e retorna 0.*/
}

/* Computa a quantidade de alunos na fila. Retorna a quantidade de alunos
 * ou -1, caso a fila for NULL.
 */
int fila_quantidade(Fila *fila) {
/*Verifica se a fila é NULL*/
  if (fila == NULL) {
    return -1;
  }
/*Retorna a quantidade caso o IF não seja validado*/
  return fila->tamanho;
}
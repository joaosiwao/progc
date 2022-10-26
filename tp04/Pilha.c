#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL 10

struct node {
  Aluno *aluno;
  struct node *proximo;
};

typedef struct node No;

struct pilha {
  No *primeiro;
};

/* Aloca espaço em memória e retorna uma pilha. */
Pilha *pilha_cria() {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->primeiro = NULL;
    return pilha;
}

/* Libera a memória de uma pilha previamente criada e atribui NULL ao ponteiro
 * pilha. Retorna 1 caso seja possível fazer a liberação e 0 caso a pilha
 * informada seja NULL. */
int pilha_libera(Pilha **pilha) {
  if (pilha != NULL) {
    if ((*pilha)->primeiro != NULL) {
      No *aux = (*pilha)->primeiro;
      do {
        alu_libera(&aux->aluno);
        aux = aux->proximo;
      } while (aux != NULL);
    }
    free(*pilha);
    *pilha = NULL;
    return 1;
  }
  return 0;
}

/* Insere um aluno na Pilha. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a pilha ou aluno sejam NULL.
 */
int pilha_push(Pilha *pilha, Aluno *aluno) {
  if(aluno == NULL || pilha == NULL){
      return -1;
  }
    /*Se a pilha ou aluno for NULL retorna -1*/

    int matricula;
    char nome[50];
    char curso[30];
    /*Declara localmente as variáveis*/

    alu_acessa(aluno, &matricula, nome, curso);
    /*Chama a função alu_acessa para acessar e armazenar os dados*/

    Aluno *alu;
    alu = pilha_busca(pilha, matricula);
    /*Buscar aluno pela matrícula e atribuir a variável alu*/

    if (alu != NULL) {
        return 0;
    }

    No *novo_aluno = (No *)malloc(sizeof(No));
    novo_aluno->aluno = aluno;
    novo_aluno->proximo = NULL;

    No *auxiliar = pilha->primeiro;

    if (auxiliar == NULL) {
        pilha->primeiro = novo_aluno;
        return 1;
    }

    for (;auxiliar != NULL; auxiliar = auxiliar->proximo) {
        if (auxiliar->proximo == NULL) {
            auxiliar->proximo = novo_aluno;
            return 1;
        }
    }
}

/* Remove um aluno na pilha. Retorna o aluno ou NULL caso a pilha esteja vazia
 * ou seja NULL. */
Aluno *pilha_pop(Pilha *pilha) {
    if(pilha == NULL){
        return NULL;
    }
    /*Não funciona assim*/
    /*No *primeiro = pilha->primeiro;
    No *segundo = primeiro->proximo;

    pilha->primeiro = segundo;
    return primeiro->aluno;*/
}

/* Recupera o primeiro aluno da pilha. Retorna o aluno ou NULL caso a pilha
 * esteja vazia ou seja NULL. */
Aluno *pilha_top(Pilha *pilha){
    if(pilha == NULL || pilha->primeiro == NULL){
        return NULL;
    }
    /*Não funciona assim*/
    /*return pilha->primeiro->aluno;*/
}

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) pilha vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a pilha seja NULL */
Aluno *pilha_busca(Pilha *pilha, int matricula) {
    if(pilha == NULL){
        return NULL;
    }

    int matricula_auxiliar;
    char nome[50];
    char curso[30];
    /*Declara variáveis locais*/

    for (No *no_auxiliar = pilha->primeiro; no_auxiliar != NULL; no_auxiliar = no_auxiliar->proximo){
        alu_acessa(no_auxiliar->aluno, &matricula_auxiliar, nome, curso);
        if (matricula_auxiliar == matricula) {
            return no_auxiliar->aluno;
        }
    }
    return NULL;
}

/* Verifica se a pilha está vazia. Retorna 1 se a pilha estiver vazia, 0 caso
 * não esteja vazia e -1 se p Pilha for NULL
 */
int pilha_vazia(Pilha *pilha) {
  if (pilha == NULL) {
    return -1;
  }
  if (pilha->primeiro == NULL) {
    return 1;
  }
  return 0;
}

/* Computa a quantidade de alunos na pilha. Retorna a quantidade de alunos
 * ou -1, caso a Pilha for NULL.
 */
int pilha_quantidade(Pilha *pilha) {
    if(pilha == NULL){
        return -1;
    }
    int quantidade = 0;
    for (No *no_auxiliar = pilha->primeiro; no_auxiliar != NULL; no_auxiliar = no_auxiliar->proximo){
        quantidade ++;
    }
    return quantidade;
}
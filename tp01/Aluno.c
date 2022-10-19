#include "Aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TAD: Aluno (matricula, nome, curso) */
typedef struct aluno Aluno;
/*Cria a struct aluno*/
    struct aluno{
        int matricula;
        char nome[50];
        char curso[30];
    };

int pegamatricula(Aluno *aluno){
    return aluno->matricula;
}
/* Aloca e retorna um aluno com os dados passados por parâmetro. Porém, para os
 * casos em que (i) pelo menos um dos parâmetros sejam nulos <-1, NULL, NULL>; e
 * (ii) o tamanho das strings nome e curso sejam maiores que os da especificação
 * (50 e 30, respectivamente), a função deve retornar NULL. */

Aluno *alu_novo(int matricula, char *nome, char *curso){
    /*Testa caso (I)*/
    if(matricula < 0 || nome == NULL || curso == NULL){
        return NULL;
    }
    /*Testa caso (II)*/
    if(strlen(nome) > 50 || strlen(curso) > 30){
        return NULL;
    }
    /*Alocação dinâmica do novo_aluno*/
    Aluno *novo_aluno = (Aluno*) malloc(sizeof(Aluno));
    novo_aluno->matricula = matricula;
    strcpy(novo_aluno->nome, nome);
    strcpy(novo_aluno->curso, curso);

    return novo_aluno;
}

/* Libera a memória de um aluno previamente criado e atribui NULL ao aluno. */
void alu_libera(Aluno **aluno){
    if (aluno != NULL) {
        free(*aluno);
        *aluno = NULL;
    }
}


/* Copia os valores de um aluno para as referências informadas. Em caso de aluno
 * NULL, atribuir valor padrão <-1, "NULL", "NULL"> aos parâmetros. */
void alu_acessa(Aluno *aluno, int *matricula, char *nome, char *curso){
    if(aluno ==  NULL){
        *matricula = -1;
        /*strcpy() para manipular string*/
        strcpy(nome, "NULL");
        strcpy(curso, "NULL");
        return;
    }
    /*Isto me informa que aluno não está NULL, então copia as informações do Aluno.*/
    *matricula = aluno->matricula;
    strcpy(nome, aluno->nome);
    strcpy(curso, aluno->curso);
    return;
}

/* Atribui novos valores aos campos de um aluno. Porém, para os casos em que (i)
 * algum dos parâmetros sejam nulos <NULL, -1, NULL, NULL>; ou (ii) o tamanho
 * das strings nome e curso sejam maiores que os da especificação (50 e 30,
 * respectivamente), a função não deve fazer a atribuição. */
void alu_atribui(Aluno *aluno, int matricula, char *nome, char *curso){
    if(aluno == NULL){
        return;
    }
    if(matricula == -1 || nome == NULL || curso == NULL){
        return;
    }
    if(strlen(nome) > 50 || strlen(curso) > 30){
        return NULL;
    }

    aluno->matricula = matricula;
    strcpy(aluno->nome, nome);
    strcpy(aluno->curso, curso);
    return;
}

/* Avalia se dois alunos são iguas. A função deve retornar 1 se os alunos
 * possuem os mesmos dados, 0 caso os dados dos alunos possuam alguma diferença
 * e -1 caso pelo menos um dos alunos seja NULL.
 */
int alu_igual(Aluno *aluno1, Aluno *aluno2) {
    if (aluno1 == NULL || aluno2 == NULL) {
        return -1;
    }
    /*A partir do IF a cima não tem aluno NULL*/
    if (aluno1->matricula != aluno2->matricula) {
        return 0;
    }
    /*Neste ponto eu sei que as matriculas são iguais, do contrário teria retornado no IF a cima*/
    if (strcmp(aluno1->nome, aluno2->nome) != 0){
        return 0;
    }
    /*Neste ponto, eu sei que se não retornou 0, os nomes são iguais.*/

    if (strcmp(aluno1->curso, aluno2->curso) != 0 ){
        return 0;
    }
    /*Se não retornou 0, todas as informações são iguais.*/
    return 1;
}

/* Retorna o tamanho em bytes do TAD aluno. */
int alu_tamanho(){
    return sizeof(Aluno);
}

#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "disciplina.h" // para usar a lista de disciplinas

// Buscar aluno pelo RGM
Aluno* buscarAluno(Aluno *lista, int rgm) {
    while (lista != NULL) {
        if (lista->rgm == rgm) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

// Inserir novo aluno na lista
void inserirAluno(Aluno **lista) {
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    if (!novo) {
        printf("Erro de alocacao\n");
        return;
    }

    printf("RGM do aluno: ");
    scanf("%d", &novo->rgm);

    printf("Nome do aluno: ");
    scanf("%s", novo->nome);

    novo->disciplinas = NULL; // começa sem disciplinas
    novo->prox = *lista;
    *lista = novo;

    printf("Aluno cadastrado com sucesso!\n");
}

// Adicionar disciplina a um aluno
void adicionarDisciplinaAluno(Aluno *aluno) {
    if (!aluno) return;

    Disciplina *nova = (Disciplina*) malloc(sizeof(Disciplina));
    if (!nova) {
        printf("Erro de alocacao\n");
        return;
    }

    printf("Nome da disciplina: ");
    scanf("%s", nova->nome);

    printf("Nota: ");
    scanf("%f", &nova->nota);

    // inserir no começo da lista de disciplinas
    nova->prox = aluno->disciplinas;
    aluno->disciplinas = nova;

    printf("Disciplina adicionada ao aluno %s!\n", aluno->nome);
}

// Listar alunos e suas disciplinas
void listarAlunos(Aluno *lista) {
    if (!lista) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    while (lista != NULL) {
        printf("Aluno: %s | RGM: %d\n", lista->nome, lista->rgm);

        Disciplina *d = lista->disciplinas;
        if (!d) {
            printf("  Nenhuma disciplina cadastrada\n");
        }
        while (d != NULL) {
            printf("  Disciplina: %s | Nota: %.2f\n", d->nome, d->nota);
            d = d->prox;
        }

        lista = lista->prox;
    }
}
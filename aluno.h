#ifndef ALUNO_H
#define ALUNO_H

#include "disciplina.h"  // você já tem

typedef struct Aluno {
    int rgm;
    char nome[50];
    Disciplina *disciplinas; // lista de disciplinas do aluno
    struct Aluno *prox;       // ponteiro para próximo aluno
} Aluno;

// Funções para manipular alunos
Aluno* buscarAluno(Aluno *lista, int rgm);
void inserirAluno(Aluno **lista);
void adicionarDisciplinaAluno(Aluno *aluno);
void listarAlunos(Aluno *lista);

#endif
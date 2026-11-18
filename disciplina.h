#ifndef DISCIPLINA_H
#define DISCIPLINA_H

typedef struct Disciplina {
    char nome[50];
    float nota;
    struct Disciplina *prox;
} Disciplina;

// funções
Disciplina* inserirFinal(Disciplina *lista);
void listar(Disciplina *lista);
Disciplina* remover(Disciplina *lista);
void calcularMedia(Disciplina *lista);

#endif
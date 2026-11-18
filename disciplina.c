#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h"

// inserir no FINAL da lista
Disciplina* inserirFinal(Disciplina *lista) {

    // cria novo nó
    Disciplina *nova = (Disciplina*) malloc(sizeof(Disciplina));

    if (nova == NULL) {
        printf("Erro de memória!\n");
        return lista;
    }

    // entrada de dados
    printf("Nome da disciplina: ");
    scanf(" %[^\n]", nova->nome);

    printf("Nota: ");
    scanf("%f", &nova->nota);

    nova->prox = NULL;

    // se lista vazia
    if (lista == NULL) {
        return nova;
    }

    // percorre até o final
    Disciplina *aux = lista;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    // liga o último com o novo
    aux->prox = nova;

    return lista;
}

// listar disciplinas
void listar(Disciplina *lista) {

    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Disciplina *aux = lista;

    printf("\n--- DISCIPLINAS ---\n");

    while (aux != NULL) {
        printf("Nome: %s\n", aux->nome);
        printf("Nota: %.2f\n", aux->nota);
        printf("------------------\n");

        aux = aux->prox;
    }
}

// remover disciplina pelo nome
Disciplina* remover(Disciplina *lista) {

    if (lista == NULL) {
        printf("Lista vazia!\n");
        return lista;
    }

    char nome[50];
    printf("Digite o nome da disciplina para remover: ");
    scanf(" %[^\n]", nome);

    Disciplina *atual = lista;
    Disciplina *anterior = NULL;

    // percorre a lista
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // não encontrou
    if (atual == NULL) {
        printf("Disciplina não encontrada!\n");
        return lista;
    }

    // remove o primeiro
    if (anterior == NULL) {
        lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);

    printf("Removido com sucesso!\n");

    return lista;
}

// calcular média das notas
void calcularMedia(Disciplina *lista) {

    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    float soma = 0;
    int count = 0;

    Disciplina *aux = lista;

    while (aux != NULL) {
        soma += aux->nota;
        count++;
        aux = aux->prox;
    }

    printf("Média das notas: %.2f\n", soma / count);
}
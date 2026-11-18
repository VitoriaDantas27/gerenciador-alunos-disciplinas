/**
 * @file estruturas.h
 * @brief Definição das estruturas de dados principais do trabalho.
 * 
 * Este módulo define as estruturas fundamentais para o gerenciamento de alunos
 * e disciplinas, seguindo os princípios de arquitetura limpa e boas práticas.
 * 
 * Estruturas:
 * - Disciplina: representa uma disciplina individual com nota (lista encadeada)
 * - Aluno: representa um aluno com seu RGM e lista de disciplinas
 * - ListaAlunos: lista sequencial estática de alunos
 * 
 * @author Daniel Costa Carvalho Martins
 * @date 2026-04-02
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

/* ============================================================================
 * CONSTANTES E DEFINIÇÕES
 * ============================================================================ */

/** @brief Capacidade máxima de alunos na lista sequencial. */
#define MAX_ALUNOS 60

/** @brief Tamanho máximo permitido para o nome de uma disciplina. */
#define TAM_MAX_DISCIPLINA 100

/** @brief Tamanho máximo permitido para o nome de um aluno. */
#define TAM_MAX_NOME_ALUNO 150

/** @brief Valor padrão para inicializar um RGM inválido. */
#define RGM_INVALIDO -1

/** @brief Código de sucesso para operações. */
#define SUCESSO 1

/** @brief Código de falha para operações. */
#define FALHA 0

/* ============================================================================
 * DEFINIÇÕES DE TIPOS
 * ============================================================================ */

/**
 * @typedef Disciplina
 * @brief Estrutura que representa uma disciplina individual.
 * 
 * Cada disciplina possui um nome e uma nota associada. As disciplinas de um
 * aluno são armazenadas em uma lista encadeada, com alocação dinâmica.
 * 
 * Campos:
 * - nome: identificação da disciplina (ex: "Cálculo I")
 * - nota: avaliação numérica da disciplina (0.0 a 10.0)
 * - proxima: apontador para a próxima disciplina na lista encadeada
 */
typedef struct Disciplina {
    char nome[TAM_MAX_DISCIPLINA];  /**< Nome identificador da disciplina */
    float nota;                     /**< Nota obtida na disciplina */
    struct Disciplina *proxima;     /**< Apontador para a próxima disciplina */
} Disciplina;

/**
 * @typedef Aluno
 * @brief Estrutura que representa um aluno individual.
 * 
 * Cada aluno é identificado unicamente por seu RGM (Registro Geral de Matrícula)
 * e possui uma lista encadeada de disciplinas. Os alunos são armazenados em uma
 * lista sequencial estática ordenada por RGM.
 * 
 * Campos:
 * - rgm: número único de identificação do aluno (chave primária)
 * - nome: nome completo do aluno (para referência)
 * - disciplinas: apontador para a lista encadeada de disciplinas
 * 
 * Invariantes:
 * - rgm deve ser maior que zero
 * - nome não pode ser vazio
 * - disciplinas pode ser NULL (aluno sem disciplinas)
 */
typedef struct {
    int rgm;                        /**< Registro Geral de Matrícula (identificador único) */
    char nome[TAM_MAX_NOME_ALUNO];  /**< Nome completo do aluno */
    Disciplina *disciplinas;        /**< Apontador para a lista de disciplinas */
} Aluno;

/**
 * @typedef ListaAlunos
 * @brief Estrutura que representa a lista sequencial de alunos.
 * 
 * A lista de alunos utiliza alocação estática com capacidade fixa de MAX_ALUNOS.
 * Os alunos devem ser mantidos em ordem crescente de RGM para permitir
 * buscas e inserções ordenadas.
 * 
 * Campos:
 * - alunos: array estático de structs Aluno
 * - quantidade: número atual de alunos cadastrados (0 <= quantidade <= MAX_ALUNOS)
 * 
 * Invariantes:
 * - quantidade nunca pode exceder MAX_ALUNOS
 * - alunos sempre devem estar ordenados por RGM em ordem crescente
 * - quantidade representa o índice do próximo aluno a ser inserido
 */
typedef struct {
    Aluno alunos[MAX_ALUNOS];   /**< Array estático de alunos */
    int quantidade;             /**< Quantidade atual de alunos cadastrados */
} ListaAlunos;

/* ============================================================================
 * FUNÇÕES DE VALIDAÇÃO
 * ============================================================================ */

/**
 * @brief Verifica se um RGM é válido.
 * 
 * Um RGM válido deve ser um número positivo (maior que zero).
 * 
 * @param rgm O RGM a ser validado.
 * @return SUCESSO se o RGM é válido, FALHA caso contrário.
 */
int rgm_eh_valido(int rgm);

/**
 * @brief Verifica se uma string de nome é válida.
 * 
 * Uma string de nome válida não pode ser vazia (primeiro caractere não deve
 * ser '\0') e deve estar com comprimento apropriado.
 * 
 * @param nome O nome a ser validado.
 * @return SUCESSO se o nome é válido, FALHA caso contrário.
 */
int nome_eh_valido(const char *nome);

/**
 * @brief Verifica se uma nota é válida.
 * 
 * Uma nota válida deve estar no intervalo [0.0, 10.0].
 * 
 * @param nota A nota a ser validada.
 * @return SUCESSO se a nota é válida, FALHA caso contrário.
 */
int nota_eh_valida(float nota);

/**
 * @brief Verifica se a lista de alunos atingiu sua capacidade máxima.
 * 
 * @param lista Apontador para a lista de alunos.
 * @return SUCESSO se a lista está cheia, FALHA caso contrário.
 */
int lista_esta_cheia(const ListaAlunos *lista);

/**
 * @brief Verifica se a lista de alunos está vazia.
 * 
 * @param lista Apontador para a lista de alunos.
 * @return SUCESSO se a lista está vazia, FALHA caso contrário.
 */
int lista_esta_vazia(const ListaAlunos *lista);

/* ============================================================================
 * FUNÇÕES DE INICIALIZAÇÃO
 * ============================================================================ */

/**
 * @brief Configura a exibição de caracteres em português do Brasil.
 * 
 * Esta função prepara o ambiente de execução para exibir corretamente
 * caracteres acentuados no console, como ç, ã, é e ô.
 * 
 * A função utiliza a localidade padrão do sistema operacional para manter
 * compatibilidade com diferentes consoles.
 * 
 * @return SUCESSO se a configuração foi aplicada, FALHA caso contrário.
 */
int configurar_saida_portugues_brasil(void);

/**
 * @brief Inicializa a lista de alunos.
 * 
 * Define a quantidade de alunos para zero, preparando a lista para
 * receber novos cadastros. Deve ser chamada uma única vez no início do programa.
 * 
 * @param lista Apontador para a estrutura ListaAlunos a ser inicializada.
 * 
 * @return SUCESSO se a inicialização foi bem-sucedida, FALHA se lista é NULL.
 */
int inicializar_lista_alunos(ListaAlunos *lista);

/* ============================================================================
 * FUNÇÕES DE MANUTENÇÃO DA LISTA SEQUENCIAL
 * ============================================================================ */

/**
 * @brief Insere um novo aluno na lista em ordem crescente de RGM.
 *
 * A função desloca os elementos necessários para manter a lista principal
 * sempre ordenada. Não permite RGMs duplicados.
 *
 * @param lista Apontador para a lista de alunos.
 * @param rgm RGM do aluno a ser inserido.
 * @param nome Nome do aluno a ser inserido.
 * @return SUCESSO se a inserção foi realizada, FALHA caso contrário.
 */
int inserir_aluno_ordenado(ListaAlunos *lista, int rgm, const char *nome);

/**
 * @brief Remove um aluno da lista a partir do seu RGM.
 *
 * Após localizar o aluno, a função desloca os elementos subsequentes para
 * preencher a posição removida, mantendo a sequência compacta.
 *
 * @param lista Apontador para a lista de alunos.
 * @param rgm RGM do aluno que será removido.
 * @return SUCESSO se a remoção foi realizada, FALHA caso contrário.
 */
int remover_aluno_por_rgm(ListaAlunos *lista, int rgm);

#endif /* ESTRUTURAS_H */

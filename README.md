# Trabalho de Estrutura de Dados 1

## Integrantes da dupla

- Daniel Costa Carvalho Martins
- Evelyn Vitória Dantas Silva Do Nascimento

## Sobre o projeto

Este projeto se trata de um trabalho da cadeira de Estrutura de Dados, a ser desenvolvido em C. A proposta consiste em implementar uma aplicação de console para gerenciamento de alunos e suas disciplinas, respeitando as estruturas e restrições definidas no enunciado.

## Problema a ser solucionado

Considere uma sala de 60 alunos, com tamanho conhecido. Cada aluno identificado pelo seu RGM possui sua própria lista de disciplinas, com tamanho variável para cada aluno.

A aplicação deve:

- realizar o cadastro em ordem do RGM de n alunos e, para cada aluno, m disciplinas, controlando a entrada com a pergunta "Mais disciplina?";
- mostrar todos os alunos cadastrados e suas respectivas disciplinas;
- procurar um aluno pelo RGM e mostrar seus dados, caso exista, ou exibir a mensagem de "não existe";
- remover um aluno localizado pelo RGM;
- mostrar a lista resultante após a remoção do aluno.

## Solução exigida

Para atender ao enunciado, a solução deve respeitar os seguintes requisitos:

- utilizar lista sequencial para armazenar os alunos;
- utilizar lista encadeada para armazenar as disciplinas de cada aluno;
- seguir a arquitetura conceitual indicada na figura fornecida;
- ser implementada em C ou Java, sendo este trabalho desenvolvido em C;
- funcionar como aplicação de console, sem interface gráfica, com menu de opções para incluir, buscar, mostrar e remover;
- garantir a inserção ordenada dos alunos pelo RGM;
- considerar que a lista sequencial possui alocação estática e a lista encadeada possui alocação dinâmica.

## Arquitetura a ser respeitada

A arquitetura conceitual do trabalho deve seguir a seguinte organização:

- uma lista sequencial principal com capacidade para 60 alunos;
- cada posição da lista principal representa um aluno identificado por sua matrícula ou RGM;
- cada aluno aponta para uma lista encadeada própria contendo suas disciplinas;
- cada nó da lista encadeada de disciplinas deve armazenar os dados da disciplina e sua nota;
- a estrutura geral representa uma lista principal estática de alunos, em que cada aluno possui uma estrutura secundária dinâmica para suas disciplinas.

Em resumo, o projeto deve modelar uma relação de "lista de alunos" contendo, em cada aluno, uma "lista de disciplinas", conforme a figura de referência.

## Divisão de funções da dupla

### Evelyn Vitória Dantas Silva Do Nascimento

Responsável pela implementação dos módulos de lista encadeada e exibição:

- lista encadeada (estrutura e operações);
- exibição (funções de apresentação de dados);
- busca (localização de elementos);
- menu (interface de interação com o usuário).

### Daniel Costa Carvalho Martins

Responsável pela implementação dos módulos principais e operações de manutenção da lista:

- estruturas (definição dos tipos principais);
- inserção ordenada (cadastro de alunos em ordem de RGM);
- remoção (deleção de alunos);
- integração (coordenação entre os módulos).

## Estado atual do projeto

Neste momento, o projeto possui a base inicial do módulo de estruturas já implementada e documentada. A parte de cadastro, inserção ordenada, busca, remoção, menu e manipulação completa das disciplinas ainda será desenvolvida nas próximas etapas.

Atualmente, já estão disponíveis:

- definição das estruturas `Disciplina`, `Aluno` e `ListaAlunos`;
- constantes de apoio, como capacidade máxima de alunos e tamanhos de campos;
- funções de validação de RGM, nome, nota e estado da lista;
- função de inicialização da lista sequencial de alunos;
- função de configuração da exibição de caracteres em português;
- programa principal com inicialização da aplicação.

## Estrutura atual dos arquivos

- `include/estruturas.h`: declarações das constantes, tipos e funções do módulo de estruturas;
- `src/estruturas.c`: implementação do módulo de estruturas e das validações iniciais;
- `src/main.c`: ponto de entrada da aplicação;
- `.vscode/c_cpp_properties.json`: configuração do compilador e do IntelliSense para o VS Code;
- `.gitignore`: exclusão de arquivos gerados na compilação.

## Funções já documentadas

O módulo de estruturas contém documentação em cabeçalhos e comentários explicativos para as seguintes funções:

- `configurar_saida_portugues_brasil()`;
- `rgm_eh_valido()`;
- `nome_eh_valido()`;
- `nota_eh_valida()`;
- `lista_esta_cheia()`;
- `lista_esta_vazia()`;
- `inicializar_lista_alunos()`.

## Como compilar

Para compilar o projeto manualmente com GCC, execute:

```powershell
gcc -Wall -Wextra -pedantic -Iinclude src/estruturas.c src/main.c -o programa.exe
```

## Como executar

Após a compilação, execute o programa com:

```powershell
.\programa.exe
```

## Observações

- o projeto está sendo desenvolvido em C, com foco em aplicação de console;
- a lista sequencial de alunos terá capacidade fixa de 60 posições;
- a lista encadeada de disciplinas será implementada em etapa posterior;
- o ambiente do VS Code já está configurado para utilizar o GCC do MinGW.

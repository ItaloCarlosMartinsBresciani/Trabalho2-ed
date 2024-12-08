#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"
#include <math.h>
#include "main_funcoes.h"
#include <limits.h>

#define TAM 100

void limpar_tela()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls"); // Para Windows
#else
    system("clear"); // Para Linux/macOS
#endif
}
// Verifica se o filme do usuário já está no sistema
void add_lista_geral(Arvore *arv_sist, elem_arv *filme, tipo_do_bloco *genero, tipo_erro *erro)
{
    if (arv_sist->Lista_Arv == NULL)
    {
        *erro = ERRO_NULL;
        return;
    }
    ListaBloco *aux = lista_verifica_elem(arv_sist->Lista_Arv, filme, erro);
    if (aux == NULL)
    {
        lista_push(arv_sist->Lista_Arv, filme, genero, erro);
        aux = lista_verifica_elem(arv_sist->Lista_Arv, filme, erro);
        if (*erro != SUCESSO)
        {
            printf("erro");
            return;
        }
        (aux->cont_ref) = 1;
    }
    else
    {
        (aux->cont_ref) += 1;
    }
}

void criar_cadastro(Arvore *arv_sist, tipo_erro *erro)
{
    *erro = SUCESSO;
    // int is_valid = 0;

    printf("\n--- CADASTRO DE USUÁRIO ---\n");
    char nome[TAM];

    char *nome_copia = (char *)malloc(strlen(nome) + 1);
    if (nome_copia == NULL)
    {
        *erro = ERRO_ALLOC;
        printf("aqui erro aloca 1\n");
        return;
    }

    char filme[TAM];
    int genero;
    // char n_usp_str[50];
    int total_filmes = 0;
    int n_usp;

    Lista *l_ord = lista_init(erro); // lista do usuário criada

    // Entrada do Numero USP
    // while (!is_valid)
    //{
    printf("\n--- INFORME O NÚMERO USP DO USUÁRIO ---\n");
    scanf("%d", &n_usp);
    getchar();
    // fgets(n_usp_str, 50, stdin);
    // n_usp_str[strcspn(n_usp_str, "\n")] = '\0';
    // is_valid = 1; // Assume que é válido
    // for (int i = 0; i < strlen(n_usp_str)+1; i++)
    //     {
    //         if (!isdigit(n_usp_str[i]))
    //         {
    //             is_valid = 0;
    //             break;
    //         }
    //     }
    //     if (!is_valid)
    //     {
    //         printf("Número USP inválido. Certifique-se de usar apenas números.\n");
    //         printf("Pressione uma tecla para continuar.\n");
    //         getchar();
    //     }
    // }
    // int n_usp = atoi(n_usp_str);

    // Entrada do nome

    printf("\n--- INFORME O NOME DO USUÁRIO ---\n");
    fgets(nome, TAM, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' do final
    strcpy(nome_copia, nome);

    while (total_filmes <= 0)
    {
        printf("Quantos filmes favoritos deseja cadastrar? ");
        scanf("%d", &total_filmes);
        getchar();
    }

    // Entrada dos filmes
    for (int i = 0; i < total_filmes; i++)
    {
        ListaBloco *p = (ListaBloco *)malloc(sizeof(ListaBloco));
        if (p == NULL)
        {
            *erro = ERRO_ALLOC;
            printf("aqui erro aloca 2\n");
            return;
        }
        else
        {
            printf("\n--- INFORME O NOME DO FILME %d ---\n", i + 1);

            // fgets(filme, 100, stdin);
            scanf(" %[^\n]", filme);
            getchar(); // Para descartar o '\n' restante no buffer

            p->dado = (elem_lista *)malloc(strlen(filme) + 1);
            if (p->dado == NULL)
            {
                *erro = ERRO_ALLOC;
                printf("aqui erro aloca 3\n");
                free(p);
                return;
            }
            strcpy(p->dado, filme);

            do
            {
                printf("\n--- SELECIONE O GÊNERO DO FILME %d ---\n", i + 1);
                printf("[1] - Ação\n");
                printf("[2] - Aventura\n");
                printf("[3] - Comédia\n");
                printf("[4] - Drama\n");
                printf("[5] - Ficção\n");
                printf("[6] - Romance\n");
                printf("[7] - Suspense\n");
                printf("[8] - Terror\n");
                printf("Escolha uma opção (1 a 8): ");
                scanf("%d", &genero);
                l_ord->vetor[genero - 1]++;
                getchar();
            } while (genero < 1 || genero > 8);

            printf("\n");
            p->tipo = genero;
            lista_push(l_ord, p->dado, &p->tipo, erro);
            add_lista_geral(arv_sist, p->dado, &p->tipo, erro);
        }
    }
    arvore_inserir(arv_sist, &arv_sist->raiz, nome_copia, &n_usp, l_ord, erro);
}

void listar_alunos(no *raiz, tipo_erro *erro)
{ // listagem de nomes de alunos e N-usp - percurso em ordem
    if (raiz == NULL)
    {
        *erro = ERRO_NULL; // Se o nó atual for nulo, simplesmente retorna
        return;
    }

    // Percorre a subárvore esquerda
    listar_alunos(raiz->esq, erro);

    // Imprime o valor do nó atual
    printf("Aluno(a): %s | N-USP: %d\n", raiz->dado, raiz->chave);

    // Percorre a subárvore direita
    listar_alunos(raiz->dir, erro);
}

// Busca usuário e informa se ele está cadastrado no sistema
void buscar_usuario(Arvore *arv_sist, tipo_erro *erro)
{
    // 1º, vamos checar se a árvore está vazia ou não
    if (arvore_vazia(arv_sist))
    {
        printf("Não há usuários cadastrados no sistema.\n");
    }
    else
    { // se não tiver vazia, deve-se checar se o usuário está no sistema
        // Vamos obter a chave (Nº USP) do usuário
        elem_chave n_usp;
        printf("Digite o número USP do usuário a ser buscado: ");
        scanf("%d", &n_usp);
        getchar(); // Limpa o buffer do teclado
        // Chama a função de buscar nó na árvore
        no *aluno = arvore_busca(arv_sist->raiz, &n_usp, erro);
        if (aluno == NULL)
        { // se o usuário não foi encontrado
            printf("Usuário não encontrado.\n");
        }
        else
        { // se o usuário foi encontrado
            printf("Usuário encontrado:\n");
            printf("Aluno(a): %s | N-USP: %d\n", aluno->dado, aluno->chave);
        }
    }
}
void listar_filmes(Lista *lista_arv, tipo_erro *erro)
{
    // Array com os nomes dos gêneros. O índice corresponde ao número do gênero.
    const char *generos[] = {
        "N/A",      // Índice 0 (não usado, apenas para facilitar o mapeamento)
        "Ação",     // Índice 1
        "Aventura", // Índice 2
        "Comédia",  // Índice 3
        "Drama",    // Índice 4
        "Ficção",   // Índice 5
        "Romance",  // Índice 6
        "Suspense", // Índice 7
        "Terror"    // Índice 8
    };

    if (lista_vazia(lista_arv, erro))
    {
        printf("Não há filmes cadastrados no sistema.\n");
    }
    else if (*erro != SUCESSO)
    {
        printf("Erro ao verificar se a lista está vazia.\n");
    }
    else
    {
        printf("Listagem de filmes cadastrados no sistema:\n");
        ListaBloco *aux = lista_arv->inicio;

        while (aux != NULL)
        {
            printf("%s | Gênero: %s\n", aux->dado, generos[aux->tipo]);
            aux = aux->prox;
        }

        printf("Listagem completa!\n");
    }
}

void buscar_filme(Arvore *arv_sist, tipo_erro *erro)
{
    char filme[TAM];
    printf("Digite o nome do filme que deseja buscar: \n");
    fgets(filme, TAM, stdin);
    filme[strcspn(filme, "\n")] = '\0';

    elem_lista *filme_copia = (elem_lista *)malloc(sizeof(elem_lista));

    if (filme_copia == NULL)
    {
        *erro = ERRO_ALLOC;
        return;
    }
    strcpy(filme_copia, filme);

    if (arvore_vazia(arv_sist))
    {
        *erro = ERRO_NULL; // árvore não inicializada ou vazia
        printf("Não há usuários cadastrados no sistema.\n");
        return;
    }

    // Busca o filme na lista da árvore
    ListaBloco *l = lista_verifica_elem(arv_sist->Lista_Arv, filme_copia, erro);

    if (l == NULL)
    {
        printf("Filme \"%s\" não mencionado!\n", filme_copia);
        *erro = ERRO_NULL;
    }
    else
    {
        if (l->cont_ref == 1)
            printf("Filme \"%s\" foi mencionado %d vez.\n", filme_copia, l->cont_ref);
        else
            printf("Filme \"%s\" foi mencionado %d vezes.\n", filme_copia, l->cont_ref);
        *erro = SUCESSO;
    }
}

int calcular_distancia_euclidiana(int *vetor1, int *vetor2)
{
    int soma = 0;
    int tamanho = 8; // Tamanho dos vetores
    for (int i = 0; i < tamanho; i++)
    {
        int diferenca = vetor1[i] - vetor2[i];
        soma += diferenca * diferenca;
    }
    return soma;
}

// Implementação da função percorrer_arvore
void percorrer_arvore(no *raiz, int *vetor_ref, int *menor_distancia, no **mais_proximo)
{
    if (raiz == NULL)
    {
        return;
    }

    // Calcula a distância para o nó atual
    int distancia = calcular_distancia_euclidiana(raiz->lista_ord->vetor, vetor_ref);

    // Atualiza a menor distância e o nó mais próximo, se necessário
    if (distancia < *menor_distancia)
    {
        *menor_distancia = distancia;
        *mais_proximo = raiz;
    }

    // Percorre os filhos à esquerda e à direita
    percorrer_arvore(raiz->esq, vetor_ref, menor_distancia, mais_proximo);
    percorrer_arvore(raiz->dir, vetor_ref, menor_distancia, mais_proximo);
}

// Função principal para recomendar colega mais proximo
void recomendar_colega(Arvore *arv_sist, tipo_erro *erro)
{
    if (arvore_vazia(arv_sist))
    {
        printf("Não há usuários cadastrados no sistema.\n");
        return;
    }

    int n_usp;
    printf("Digite o seu número USP: ");
    scanf("%d", &n_usp);

    no *aluno = arvore_busca(arv_sist->raiz, &n_usp, erro);
    if (aluno == NULL)
    {
        printf("Usuário com Nº USP %d não está cadastrado no sistema.\n", n_usp);
        return;
    }

    int menor_distancia = INT_MAX;
    no *mais_proximo = NULL;

    // Percorre a árvore para encontrar o nó mais próximo
    percorrer_arvore(arv_sist->raiz, aluno->lista_ord->vetor, &menor_distancia, &mais_proximo);

    if (mais_proximo != NULL)
    {
        printf("O colega mais semelhante é o usuário com Nº USP %d, com uma distância de %d.\n", mais_proximo->chave, menor_distancia);
    }
    else
    {
        printf("Nenhum colega encontrado.\n");
    }
}

// void recomendar_oposto();
// void exportar_dados();
// void exibir_dados_arvore();
// void remover_usuario();

// Função que diz qual é o filme mais mencionado
void mais_mencionado(Lista *lista_arv, tipo_erro *erro)
{
    // Array com os nomes dos gêneros. O índice corresponde ao número do gênero.
    const char *generos[] = {
        "N/A",      // Índice 0 (não usado, apenas para facilitar o mapeamento)
        "Ação",     // Índice 1
        "Aventura", // Índice 2
        "Comédia",  // Índice 3
        "Drama",    // Índice 4
        "Ficção",   // Índice 5
        "Romance",  // Índice 6
        "Suspense", // Índice 7
        "Terror"    // Índice 8
    };

    if (lista_vazia(lista_arv, erro))
    {
        printf("Não há filmes cadastrados no sistema.\n");
        return;
    }
    ListaBloco *aux = lista_arv->inicio;
    ListaBloco *melhor_filme = lista_arv->inicio;
    if (*erro != SUCESSO)
    {
        printf("Erro ao verificar se a lista está vazia.\n");
    }
    else
    {
        while (aux != NULL)
        {
            if (aux->cont_ref > melhor_filme->cont_ref)
            {
                melhor_filme = aux; // atualiza o melhor filme
            }
            aux = aux->prox;
        }
    }
    printf("Filme mais mencionado:\n");
    printf("%s | Gênero: %s\n", melhor_filme->dado, generos[melhor_filme->tipo]);
}

void exibir_menu()
{
    printf("\n\n");
    printf("\n==============================\n");
    printf("    SISTEMA DO CINE USP     \n");
    printf("==============================\n");
    printf("1) Criar um cadastro\n");
    printf("2) Listar todos os alunos cadastrados\n");
    printf("3) Buscar um usuário no sistema\n");
    printf("4) Listar filmes diferentes em ordem alfabética\n");
    printf("5) Buscar um filme no sistema\n");
    printf("6) Recomendar colega para cinema\n");
    printf("7) Recomendar colega com perfil oposto\n");
    printf("8) Exportar dados para arquivo texto\n");
    printf("9) Exibir dados técnicos da árvore\n");
    printf("10) Remover usuário do cadastro\n");
    printf("11) Filme mais mencionado\n");
    printf("0) Sair\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}
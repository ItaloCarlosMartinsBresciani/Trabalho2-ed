#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"
#include <math.h>
#include "main_funcoes.h"
#include <locale.h>
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

void auxiliar_cadastro(Arvore *arv_sist, Lista *l_ord, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    char filme[TAM];
    int genero;
    int total_filmes = 0;
    char filmes_str[TAM];
    int is_valid = 0;
    // Laço do-while para informar quantos filmes devem ser cadastrados
    do
    {
        printf("Quantos filmes favoritos deseja cadastrar? ");
        fgets(filmes_str, TAM, stdin);
        filmes_str[strcspn(filmes_str, "\n")] = '\0'; // Remove o '\n' do final

        is_valid = 1; // Assume que é válido

        // Verifica se a entrada contém apenas dígitos
        for (size_t i = 0; i < strlen(filmes_str); i++)
        {
            if (!isdigit(filmes_str[i]))
            {
                is_valid = 0; // Invalida se encontrar algo que não seja dígito
                break;
            }
        }

        if (is_valid)
        {
            total_filmes = atoi(filmes_str); // Converte para inteiro
            if (total_filmes <= 0)
            {
                is_valid = 0; // Não aceita valores negativos ou zero
            }
        }

        if (!is_valid)
        {
            printf("Entrada inválida. Insira apenas números positivos maiores que zero.\n");
            printf("\n");
        }
    } while (!is_valid);


    int i = 0;
    do
    {
        ListaBloco *p = (ListaBloco *)malloc(sizeof(ListaBloco));
        if (p == NULL)
        { // verifica se a alocação de memória foi realizada com sucesso
            *erro = ERRO_ALLOC;
            return;
        }
        else // se a alocação foi bem sucedida
        {
            printf("\n--- INFORME O NOME DO FILME %d ---\n", i + 1);

            // fgets(filme, 100, stdin);
            scanf(" %[^\n]", filme);
            getchar(); // Para descartar o '\n' restante no buffer

            p->dado = (elem_lista *)malloc(strlen(filme) + 1);
            if (p->dado == NULL)
            {
                *erro = ERRO_ALLOC;
                free(p);
                return;
            }
            strcpy(p->dado, filme);


            // Ver se o filme informado está na lista geral
            ListaBloco *l = lista_verifica_elem(arv_sist->Lista_Arv, p->dado, erro);
            if (l != NULL)
            { // FILME JÁ CADASTRADO NA LISTA GERAL
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
                ListaBloco *m = lista_verifica_elem(l_ord, l->dado, erro); // Verifica se o filme está na lista do user
                if (m == NULL)
                { // Se o filme não está na lista de usuários
                    lista_push(l_ord, l->dado, &l->tipo, erro); // insere o filme na lista do usuários
                    i++; // incrementa o i pois o filme foi inserido na lista de usuários
                    printf("Filme cadastrado com sucesso na lista de favoritos! O genêro é %s\n", generos[l->tipo]);
                    l->cont_ref++;

                }else
                { // Se o filme está na lista de usuários
                    printf("Esse filme já foi cadastrado na sua lista de favoritos. Tente outro!\n");
                    continue; // volta ao início do laço

                }
            }
            else
            { // FILME NÃO CADASTRADO NA LISTA GERAL
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
                    getchar(); // limpa o buffer
                } while (genero < 1 || genero > 8);

                printf("\n");
                p->tipo = genero;
                lista_push(l_ord, p->dado, &p->tipo, erro);
                i++; // incrementa o i pois o filme foi inserido na lista de usuários
                printf("Filme cadastrado com sucesso!\n");
                add_lista_geral(arv_sist, p->dado, &p->tipo, erro);
            }
        }
        
    }while(i < total_filmes);
}
// Função que cadastra um novo usuário no sistema
void criar_cadastro(Arvore *arv_sist, tipo_erro *erro) // tem que verificar se o n_usp já existe
{
    *erro = SUCESSO;
    int is_valid = 0;
    setlocale(LC_ALL, "Portuguese");
    printf("\n--- CADASTRO DE USUÁRIO ---\n");
    char nome[TAM];

    char *nome_copia = (char *)malloc(strlen(nome) + 1);
    if (nome_copia == NULL)
    {
        *erro = ERRO_ALLOC;
        return;
    }

    char n_usp_str[50];
    int n_usp;

    Lista *l_ord = lista_init(erro); // lista do usuário criada

    // Entrada do Numero USP

    do
    {
        printf("\n--- INFORME O NÚMERO USP DO USUÁRIO ---\n");
        fgets(n_usp_str, sizeof(n_usp_str), stdin);
        n_usp_str[strcspn(n_usp_str, "\n")] = '\0'; // Remove o '\n', se presente

        is_valid = 1; // Assume que é válido

        // Verifica se todos os caracteres são dígitos
        for (size_t i = 0; i < strlen(n_usp_str); i++)
        {
            if (!isdigit(n_usp_str[i]))
            {
                is_valid = 0; // Se encontrar algo que não é número, invalida
                break;
            }
        }

        if (!is_valid || strlen(n_usp_str) == 0 || atoi(n_usp_str) < 0)
        {
            printf("Número USP inválido. Certifique-se de usar apenas números maiores ou igual a zero.\n");
            printf("Pressione ENTER para tentar novamente.\n");
            getchar(); // Aguarda o Enter do usuário
        }
        n_usp = atoi(n_usp_str); // Converte a string para número inteiro
        no *aux = arvore_busca(arv_sist->raiz, &n_usp, erro);
        if (aux != NULL)
        {
            printf("N-USP já cadastrado. Tente outro número ou cadastre os filmes.\n");
            is_valid = 0;
        }

    } while (!is_valid);

    printf("Número USP válido: %d\n", n_usp);

    // Entrada e validação do nome
    do
    {
        printf("\n--- INFORME O NOME DO USUÁRIO ---\n");
        fgets(nome, TAM, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' do final

        is_valid = 1; // Assume que é válido

        // Verifica se o nome contém apenas letras e espaços
        for (size_t i = 0; i < strlen(nome); i++)
        {
            if (!isalpha(nome[i]) && nome[i] != ' ')
            {
                is_valid = 0; // Invalida o nome se encontrar algo diferente
                break;
            }
        }

        if (!is_valid || strlen(nome) == 0)
        {
            printf("Nome inválido. Certifique-se de usar apenas letras e espaços.\n");
            printf("Aperte uma tecla para continuar!");
            getchar();
        }
    } while (!is_valid);

    // Copia o nome validado
    strcpy(nome_copia, nome);

    // Entrada e validação de filmes favoritos
    auxiliar_cadastro(arv_sist, l_ord, erro);

    arvore_inserir(arv_sist, &arv_sist->raiz, nome_copia, &n_usp, l_ord, erro);
}
// Função que lista os nomes de todos os alunos cadastrados no sistema
void listar_alunos(no *raiz, tipo_erro *erro)
{ // listagem de nomes de alunos e N-usp - percurso em ordem
    setlocale(LC_ALL, "Portuguese");
    if (raiz == NULL)
    {
        return;
    }
    // Percorre a subárvore esquerda
    listar_alunos(raiz->esq, erro);

    // Imprime o valor do nó atual
    printf("Aluno(a): %s | N-USP: %d\n", raiz->dado, raiz->chave);

    // Percorre a subárvore direita
    listar_alunos(raiz->dir, erro);
}

void arquivo_listar_alunos(no *raiz, FILE *arquivo, tipo_erro *erro)
{ // listagem de nomes de alunos e N-usp - percurso em ordem
    setlocale(LC_ALL, "Portuguese");
    if (raiz == NULL)
    {
        return;
    }
    // Percorre a subárvore esquerda
    arquivo_listar_alunos(raiz->esq, arquivo, erro);

    // Imprime no arquivo o valor do nó atual
    fprintf(arquivo, "N-USP: %d | Nome: %s\n", raiz->chave, raiz->dado);
    fprintf(arquivo, "Listagem de filmes cadastrados por %s:\n", raiz->dado);
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

    if (raiz->lista_ord != NULL && raiz->lista_ord->inicio != NULL)
    {
        ListaBloco *aux = raiz->lista_ord->inicio;
        while (aux != NULL)
        {
            fprintf(arquivo, "%s | Gênero: %s\n\n", aux->dado, generos[aux->tipo]);
            aux = aux->prox;
        }
    }

    // Percorre a subárvore direita
    arquivo_listar_alunos(raiz->dir, arquivo, erro);
}

// Busca usuário e informa se ele está cadastrado no sistema, além de informar os filmes cadastrados por ele
void buscar_usuario(Arvore *arv_sist, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---BUSCAR ALUNO---\n");
    // 1º, vamos checar se a árvore está vazia ou não
    if (arvore_vazia(arv_sist))
    {
        printf("Não há usuários cadastrados no sistema.\n");
        limpar_tela();
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
            printf("Listagem de filmes cadastrados por %s:\n", aluno->dado);

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

            ListaBloco *aux = aluno->lista_ord->inicio;

            while (aux != NULL)
            {
                printf("%s | Gênero: %s\n\n", aux->dado, generos[aux->tipo]);
                aux = aux->prox;
            }

            printf("Listagem completa!\n");
        }
    }
}
// Lista filmes da lista geral e sua contagem de referências
void listar_filmes(Lista *lista_arv, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---LISTAGEM DE FILMES---\n");

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
            printf("%s | Gênero: %s | Menções: %d\n\n", aux->dado, generos[aux->tipo], aux->cont_ref);
            aux = aux->prox;
        }

        printf("Listagem completa!\n");
    }
}
// Função que busca um filme na lista geral e informa quantas vezes ele foi mencionado
void buscar_filme(Arvore *arv_sist, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---BUSCAR FILME---\n");

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
        printf("Não há filmes cadastrados no sistema.\n");
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
void percorrer_arvore(no *raiz, int *vetor_ref, int *menor_distancia, no **mais_proximo, no *usuario_atual)
{
    if (raiz == NULL)
    {
        return;
    }

    if (raiz == usuario_atual)
    {
        percorrer_arvore(raiz->esq, vetor_ref, menor_distancia, mais_proximo, usuario_atual);
        percorrer_arvore(raiz->dir, vetor_ref, menor_distancia, mais_proximo, usuario_atual);
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
    percorrer_arvore(raiz->esq, vetor_ref, menor_distancia, mais_proximo, usuario_atual);
    percorrer_arvore(raiz->dir, vetor_ref, menor_distancia, mais_proximo, usuario_atual);
}

// Função principal para recomendar colega mais proximo
void recomendar_colega(Arvore *arv_sist, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---RECOMENDAÇÃO DE COLEGA MAIS SIMILAR PARA IR AO CINEMA---\n");

    if (arvore_vazia(arv_sist))
    {
        printf("Não há usuários cadastrados no sistema.\n");
        return;
    }

    int n_usp;
    printf("Digite o seu número USP: ");
    scanf("%d", &n_usp);
    getchar(); // Limpa o buffer do teclado

    no *aluno = arvore_busca(arv_sist->raiz, &n_usp, erro);
    if (aluno == NULL)
    {
        printf("Usuário com Nº USP %d não está cadastrado no sistema.\n", n_usp);
        return;
    }

    int menor_distancia = INT_MAX;
    no *mais_proximo = NULL;

    // Percorre a árvore para encontrar o nó mais próximo
    percorrer_arvore(arv_sist->raiz, aluno->lista_ord->vetor, &menor_distancia, &mais_proximo, aluno);

    if (mais_proximo != NULL)
    {
        printf("O colega mais semelhante é o %s com Nº USP %d.\n", mais_proximo->dado, mais_proximo->chave);
    }
    else
    {
        printf("Nenhum colega encontrado.\n");
    }
}

void percorrer_arvore_oposto(no *raiz, int *vetor_ref, int *maior_distancia, no **menos_proximo, no *usuario_atual)
{
    if (raiz == NULL)
    {
        return;
    }

    if (raiz == usuario_atual)
    {
        percorrer_arvore_oposto(raiz->esq, vetor_ref, maior_distancia, menos_proximo, usuario_atual);
        percorrer_arvore_oposto(raiz->dir, vetor_ref, maior_distancia, menos_proximo, usuario_atual);
        return;
    }

    // Calcula a distância para o nó atual
    int distancia = calcular_distancia_euclidiana(raiz->lista_ord->vetor, vetor_ref);

    // Atualiza a menor distância e o nó mais próximo, se necessário
    if (distancia > *maior_distancia)
    {
        *maior_distancia = distancia;
        *menos_proximo = raiz;
    }

    // Percorre os filhos à esquerda e à direita
    percorrer_arvore_oposto(raiz->esq, vetor_ref, maior_distancia, menos_proximo, usuario_atual);
    percorrer_arvore_oposto(raiz->dir, vetor_ref, maior_distancia, menos_proximo, usuario_atual);
}
// Função principal para recomendar colega menos proximo
void recomendar_colega_oposto(Arvore *arv_sist, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---RECOMENDAÇÃO DE COLEGA MENOS SIMILAR PARA IR AO CINEMA---\n");

    if (arvore_vazia(arv_sist))
    {
        printf("Não há usuários cadastrados no sistema.\n");
        return;
    }

    int n_usp;
    printf("Digite o seu número USP: ");
    scanf("%d", &n_usp);
    getchar(); // Limpa o buffer do teclado

    no *aluno = arvore_busca(arv_sist->raiz, &n_usp, erro);
    if (aluno == NULL)
    {
        printf("Usuário com Nº USP %d não está cadastrado no sistema.\n", n_usp);
        return;
    }

    int maior_distancia = INT_MIN;
    no *menos_proximo = NULL;

    // Percorre a árvore para encontrar o nó mais próximo
    percorrer_arvore_oposto(arv_sist->raiz, aluno->lista_ord->vetor, &maior_distancia, &menos_proximo, aluno);

    if (menos_proximo != NULL)
    {
        printf("O colega menos semelhante é o %s com Nº USP %d\n", menos_proximo->dado, menos_proximo->chave);
    }
    else
    {
        printf("Nenhum colega encontrado.\n");
    }
}
// Função que exporta os dados do sistema para um arquivo texto
void exportar_dados(Arvore *arv_sist, tipo_erro *erro)
{
    FILE *arquivo;
    arquivo = fopen("dados_cine_usp.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // printar todos os dados dos nos da arvore
    fprintf(arquivo, "\n---DADOS DOS USUARIOS---\n");
    arquivo_listar_alunos(arv_sist->raiz, arquivo, erro);
    // imprimir no arquivo texto todos os filmes cadastrados

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

    if (lista_vazia(arv_sist->Lista_Arv, erro))
    {
        fprintf(arquivo, "Não há filmes cadastrados no sistema.\n");
    }
    else if (*erro != SUCESSO)
    {
        fprintf(arquivo, "Erro ao verificar se a lista está vazia.\n");
    }
    else
    {
        fprintf(arquivo, "==========================================\n");
        fprintf(arquivo, "Listagem de filmes cadastrados no sistema:\n");
        ListaBloco *aux = arv_sist->Lista_Arv->inicio;

        while (aux != NULL)
        {
            fprintf(arquivo, "%s | Gênero: %s | Menções: %d\n\n", aux->dado, generos[aux->tipo], aux->cont_ref);
            aux = aux->prox;
        }
    }
    fprintf(arquivo, "===============================\n");
    fprintf(arquivo, "\n---DADOS TÉCNICOS DA ARVORE---\n");
    fprintf(arquivo, "Dados da árvore do sistema:\n");
    fprintf(arquivo, "Total de nós: %d\n", arv_sist->totalNos);
    fprintf(arquivo, "Altura da árvore: %d\n", alturaArvore(arv_sist->raiz));
    // listar todos os filmes cadastrados

    fclose(arquivo);
    printf("Dados exportados com sucesso!\n");
}

void exibir_dados_arvore(Arvore *arv_sist, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n--- DADOS DA ÁRVORE ---\n");
    printf("\n");
    printf("Total de Nós: %d\n", arv_sist->totalNos);
    printf("Altura da Árvore: %d\n", alturaArvore(arv_sist->raiz));

    int n_usp = 0;
    printf("Digite o N-USP do nó que deseja verificar: ");
    scanf("%d", &n_usp);
    getchar(); // Limpa o buffer do teclado

    no *aux = arvore_busca(arv_sist->raiz, &n_usp, erro);
    int maior_altura_dir = alturaArvore(aux->dir);
    int maior_altura_esq = alturaArvore(aux->esq);
    int diferenca = abs(maior_altura_dir - maior_altura_esq);
    printf("Maior diferença entre alturas que existe entre as sub-árvores do nó com N-USP %d: %d\n", n_usp, diferenca);

    printf("\n---FIM EXIBIÇÃO DOS DADOS---\n");
}
// Função que remove um usuário do sistema
void remover_usuario(Arvore *arv_sist, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---REMOÇÃO DE USUÁRIO---\n");

    // primeiro, vemos se a árvore do sistema está vazia
    if (arvore_vazia(arv_sist))
    {
        printf("Não foi possível remover um usuário. Não há usuários cadastrados no sistema!\n");
        return;
    }
    else
    { // caso em que a árvore não está vazia e é necessário remover o usuário
        // Vamos obter a chave (Nº USP) do usuário
        elem_chave n_usp;
        printf("Digite o número USP do usuário a ser removido: ");
        scanf("%d", &n_usp);
        getchar(); // Limpa o buffer do teclado
        // Chama a função de buscar nó na árvore
        no *aluno = arvore_busca(arv_sist->raiz, &n_usp, erro);
        if (aluno == NULL)
        { // se o usuário não foi encontrado
            printf("Usuário não encontrado.\n");
            return;
        }
        else
        { // se o usuário foi encontrado, chamamos a função para remover o nó
            // antes de remover o usuário da árvore do sistema, é preciso ver como isso afeta a lista geral
            // lógica de tratamento da lista geral:
            // primeiro, vamos obter um ponteiro o primeiro filme que tá na lista de filmes do usuário

            ListaBloco *aux_usu = lista_verifica_elem(aluno->lista_ord, aluno->lista_ord->inicio->dado, erro);
            while (aux_usu != NULL)
            {
                // agora temos um ponteiro para o ListaBloco
                // agora vamos procurar ele na lista_geral com lista_Verifica_elem
                ListaBloco *aux_geral = lista_verifica_elem(arv_sist->Lista_Arv, aux_usu->dado, erro);
                aux_geral->cont_ref -= 1;
                if (aux_geral->cont_ref == 0) // caso em que o filme não tem mais referências
                {
                    lista_pop(arv_sist->Lista_Arv, aux_geral->dado, erro); // remove o filme sem referências da liista geral
                }
                lista_pop(aluno->lista_ord, aux_usu->dado, erro);
                aux_usu = aux_usu->prox;
            }

            arvore_remover(arv_sist, &arv_sist->raiz, &aluno->chave, erro);
            if (*erro != SUCESSO)
            {
                printf("Erro ao tentar remover usuário.\n");
            }
            else
            {
                printf("Usuário removido com sucesso!\n");
            }
        }
    }
}

// Função que diz qual é o filme mais mencionado
void mais_mencionado(Lista *lista_arv, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---FILME MAIS MENCIONADO---\n");
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
    printf("%s | Gênero: %s | Menções:%d\n", melhor_filme->dado, generos[melhor_filme->tipo], melhor_filme->cont_ref);
}
// Função auxiliar para cadastrar filmes
void cadastrar_filmes(Arvore *arv_sistema, tipo_erro *erro)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\n---CADASTRO DE FILMES---\n");
    int n_usp;
    char n_usp_str[TAM];
    int is_valid = 0;

    do
    {
        printf("\n--- INFORME O NÚMERO USP DO USUÁRIO ---\n");
        fgets(n_usp_str, sizeof(n_usp_str), stdin);
        n_usp_str[strcspn(n_usp_str, "\n")] = '\0'; // Remove o '\n', se presente

        is_valid = 1; // Assume que é válido

        // Verifica se todos os caracteres são dígitos
        for (size_t i = 0; i < strlen(n_usp_str); i++)
        {
            if (!isdigit(n_usp_str[i]))
            {
                is_valid = 0; // Se encontrar algo que não é número, invalida
                break;
            }
        }

        if (!is_valid || strlen(n_usp_str) == 0)
        {
            printf("Número USP inválido. Certifique-se de usar apenas números.\n");
            printf("Pressione ENTER para tentar novamente.\n");
            getchar(); // Aguarda o Enter do usuário
        }

    } while (!is_valid);

    // Converte a string para número inteiro
    n_usp = atoi(n_usp_str);
    printf("Número USP válido: %d\n", n_usp);

    no *aux = arvore_busca(arv_sistema->raiz, &n_usp, erro);
    if (aux == NULL)
    {
        *erro = ERRO_NULL;
        printf(" N-USP não cadastrado. Realize seu primeiro cadastro.\n");
        return;
    }
    else
    {
        auxiliar_cadastro(arv_sistema, aux->lista_ord, erro);
        printf("Cadastro feito com sucesso.\n");
    }
}
// Função que exibe o menu do sistema
void exibir_menu()
{
    setlocale(LC_ALL, "Portuguese");
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
    printf("12) Cadastrar filmes\n");
    printf("0) Sair\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}
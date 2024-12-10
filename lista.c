#include "lista.h"
#include "erro.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

Lista *lista_init(tipo_erro *erro) // Função para inicializar uma lista
{
    // Aloca memória para uma nova estrutura Lista
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    // Verifica se a alocação de memória falhou
    if (lista == NULL)
    {
        *erro = ERRO_ALLOC; // Define o erro de alocação
        return NULL;        // Retorna NULL para indicar falha na inicialização
    }

    // Inicializa o ponteiro para o início da lista como NULL (lista vazia)
    lista->inicio = NULL;

    // Inicializa o vetor dentro da estrutura Lista com zeros
    memset(lista->vetor, 0, sizeof(lista->vetor));

    // Define o código de sucesso na variável erro
    *erro = SUCESSO;

    // Retorna o ponteiro para a nova estrutura Lista inicializada
    return lista;
}

void lista_push(Lista *lista, elem_lista *dado, tipo_do_bloco *tipo, tipo_erro *erro)
{
    ListaBloco *atual, *ant, *bloco;

    // Aloca memória para um novo bloco da lista
    bloco = (ListaBloco *)malloc(sizeof(ListaBloco));
    if (bloco == NULL)
    {
        *erro = ERRO_ALLOC; // Define erro de alocação de memória
        return;             // Retorna sem realizar a inserção
    }
    else
    {
        *erro = SUCESSO;     // Define sucesso na alocação de memória
        bloco->dado = dado;  // Armazena o dado no novo bloco
        bloco->tipo = *tipo; // Copia o tipo do bloco recebido como argumento para o novo bloco

        // Verifica se a lista está vazia ou se o novo dado é menor que o primeiro elemento
        if ((lista->inicio == NULL) || (strcmp(dado, lista->inicio->dado) < 0))
        {
            // Insere o novo bloco como o primeiro da lista
            bloco->prox = lista->inicio; // Aponta o novo bloco para o início atual
            lista->inicio = bloco;       // Atualiza o início da lista para o novo bloco
        }
        else
        {
            // Caso o novo dado seja maior, encontra a posição correta para inserção
            ant = NULL;            // Inicializa o ponteiro para o anterior como NULL
            atual = lista->inicio; // Começa pelo primeiro elemento da lista

            // Percorre a lista até encontrar a posição onde o dado seja maior ou igual ao atual
            while ((atual != NULL) && (strcmp(atual->dado, dado) < 0))
            {
                ant = atual;         // Atualiza o anterior para o atual
                atual = atual->prox; // Move para o próximo elemento
            }

            // Insere o novo bloco entre o anterior e o atual
            bloco->prox = atual; // Aponta o novo bloco para o próximo encontrado
            ant->prox = bloco;   // Aponta o bloco anterior para o novo bloco
        }
    }
}

ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado, tipo_erro *erro)
{
    // Verifica se o ponteiro para a lista é NULL
    if (lista == NULL)
    {
        *erro = ERRO_NULL; // Define erro caso a lista seja NULL
        return NULL;       // Retorna NULL indicando que a lista não existe
    }

    // Verifica se a lista está vazia
    if (lista_vazia(lista, erro) == true)
    {
        // Caso a verificação da lista vazia tenha falhado
        if (*erro != SUCESSO) // Se o erro não for SUCESSO, a verificação falhou
        {
            return NULL; // Retorna NULL indicando falha na verificação
        }
        return NULL; // Retorna NULL pois a lista está vazia
    }

    // Começa a busca pelo primeiro elemento da lista
    ListaBloco *atual = lista->inicio;

    // Percorre a lista procurando o dado
    while (atual != NULL)
    {
        // Se o dado do bloco atual for igual ao dado procurado
        if (strcmp(atual->dado, dado) == 0)
        {
            *erro = SUCESSO; // Define erro como SUCESSO, pois o elemento foi encontrado
            return atual;    // Retorna o bloco que contém o dado
        }
        atual = atual->prox; // Avança para o próximo bloco da lista
    }

    *erro = SUCESSO; // Define erro como SUCESSO, pois a busca foi concluída (mesmo sem encontrar)
    return NULL;     // Retorna NULL indicando que o dado não foi encontrado na lista
}

ListaBloco *lista_pop(Lista *lista, elem_lista *dado, tipo_erro *erro) /*, int *erro*/
{
    ListaBloco *p, *ant;

    // Verifica se a lista está vazia ou se o dado não está no início da lista
    if (lista->inicio == NULL || (strcmp(dado, lista->inicio->dado) < 0))
    {
        *erro = ERRO_NULL; // Define erro indicando que a lista está vazia ou o dado não foi encontrado
        return NULL;       // Retorna NULL, pois não pode remover o elemento
    }
    else if ((strcmp(dado, lista->inicio->dado) == 0))
    {
        // Se o dado está no início da lista, remove o primeiro bloco
        p = lista->inicio;                   // Armazena o ponteiro para o bloco a ser removido
        lista->inicio = lista->inicio->prox; // Atualiza o início da lista para o próximo bloco
        free(p);                             // Libera a memória do bloco removido
    }
    else
    {
        // Caso o dado não esteja no início, percorre a lista para encontrar o dado
        ant = NULL;        // Inicializa o ponteiro para o bloco anterior como NULL
        p = lista->inicio; // Começa a busca a partir do primeiro bloco

        // Percorre a lista até encontrar o dado ou alcançar o final
        while ((p != NULL) && (strcmp(dado, p->dado) > 0))
        {
            ant = p;     // Atualiza o ponteiro para o bloco anterior
            p = p->prox; // Avança para o próximo bloco
        }

        // Verifica se encontrou o dado e realiza a remoção
        if ((p != NULL) && (strcmp(dado, p->dado) == 0))
        {
            ant->prox = p->prox; // Atualiza o ponteiro do bloco anterior para o próximo do bloco removido
            free(p);             // Libera a memória do bloco removido
        }
        else
        {
            *erro = ERRO_POP_VAZIO; // Define erro indicando que o dado não foi encontrado na lista
        }
    }

    return NULL; // Retorna NULL, pois a função não retorna o valor removido
}

bool lista_vazia(Lista *lista, tipo_erro *erro)
{
    // Verifica se o ponteiro para a lista é NULL
    if (lista == NULL)
    {
        *erro = ERRO_NULL; // Define erro indicando que a lista é NULL
        return true;       // Retorna true, pois a lista não existe
    }

    // Verifica se o início da lista é NULL (lista vazia)
    if (lista->inicio == NULL)
    {
        *erro = SUCESSO; // Define sucesso, pois a lista está vazia
        return true;     // Retorna true, pois a lista está vazia
    }

    *erro = SUCESSO; // Define sucesso, pois a lista não está vazia
    return false;    // Retorna false, pois a lista contém elementos
}

void lista_print(Lista *lista, tipo_erro *erro)
{
    // Verifica se o ponteiro para a lista é NULL
    if (lista == NULL)
    {
        *erro = ERRO_NULL; // Define erro indicando que a lista é NULL
        return;            // Retorna sem fazer nada, pois a lista não pode ser impressa
    }

    // Verifica se a lista está vazia
    if (lista_vazia(lista, erro) == true)
    {
        // Se a verificação de lista vazia falhou
        if (erro != SUCESSO) // Se o erro não for SUCESSO, significa que houve falha na verificação
        {
            return; // Retorna sem fazer nada, pois a verificação não foi concluída corretamente
        }

        *erro = ERRO_NULL; // Define erro indicando que a lista está vazia e não pode ser impressa
        return;            // Retorna, pois não há elementos para imprimir
    }

    // Inicializa o ponteiro atual para o primeiro bloco da lista
    ListaBloco *atual = lista->inicio;

    // Percorre a lista e imprime os dados de cada bloco
    while (atual != NULL)
    {
        printf("%s\n", atual->dado); // Imprime o dado do bloco atual
        atual = atual->prox;         // A
    }

    *erro = SUCESSO; // Define erro como SUCESSO, indicando que a impressão foi bem-sucedida
}

void lista_libera(Lista *lista, tipo_erro *erro)
{
    // Verifica se o ponteiro para a lista é NULL
    if (lista == NULL)
    {
        *erro = ERRO_NULL;  // Define erro indicando que a lista é NULL
        return;             // Retorna sem fazer nada, pois não pode liberar uma lista inexistente
    }

    // Verifica se a lista está vazia
    if (lista_vazia(lista, erro) == true)
    {
        // Se a verificação de lista vazia falhou
        if (erro != SUCESSO) // Se o erro não for SUCESSO, significa que houve falha na verificação
        {
            return;  // Retorna sem fazer nada, pois a verificação não foi concluída corretamente
        }
        
        *erro = ERRO_NULL;  // Define erro indicando que a lista está vazia e não pode ser liberada
        return;             // Retorna, pois não há elementos para liberar
    }

    // Inicializa o ponteiro atual para o primeiro bloco da lista
    ListaBloco *atual = lista->inicio;
    ListaBloco *proximo; // Ponteiro para o próximo bloco

    // Percorre a lista e libera a memória de cada bloco
    while (atual != NULL)
    {
        proximo = atual->prox; // Armazena o ponteiro para o próximo bloco
        free(atual);           // Libera a memória do bloco atual
        atual = proximo;       // Avança para o próximo bloco
    }

    // Libera a memória da estrutura da lista
    free(lista);
    *erro = SUCESSO;  // Define erro como SUCESSO, indicando que a liberação foi bem-sucedida
}


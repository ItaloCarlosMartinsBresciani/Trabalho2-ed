#include "lista.h"
#include "erro.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

Lista *lista_init(tipo_erro *erro) // ok
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (lista == NULL)
    {
        *erro = ERRO_ALLOC; // erro de alocação de memória
        return NULL;
    }
    //lista->fim = NULL;
    lista->inicio = NULL;
    memset(lista->vetor, 0, sizeof(lista->vetor)); // Inicializa todos os elementos com 0
    *erro = SUCESSO;                               // lista inicializada com sucesso
    return lista;
}

void lista_push(Lista *lista, elem_lista *dado, tipo_do_bloco *tipo, tipo_erro *erro)
{
    ListaBloco *atual, *ant, *bloco;

    bloco = (ListaBloco *)malloc(sizeof(ListaBloco));
    if (bloco == NULL)
    {
        *erro = ERRO_ALLOC; // erro de alocação de memória
        return;
    }
    else
    {
        *erro = SUCESSO; // alocação de memória bem sucedida
        bloco->dado = dado;
        bloco->tipo = *tipo; // tipo passado por referência é atribuído ao campo bloco->tipo
        
        if ((lista->inicio == NULL) || (strcmp(dado, lista->inicio->dado) < 0))
        { // caso em que o bloco < 1º da lista
            bloco->prox = lista->inicio;
            lista->inicio = bloco;
        }
        else
        { // caso em que o bloco > 1º da lista
            ant = NULL;
            atual = lista->inicio;
            while ((atual != NULL) && (strcmp(atual->dado, dado) < 0))
            {
                ant = atual;
                atual = atual->prox;
            }
            bloco->prox = atual;
            ant->prox = bloco;
        }
    }
}

ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado, tipo_erro *erro)
{
    if (lista == NULL)
    {
        *erro = ERRO_NULL;
        return NULL;
    }
    if (lista_vazia(lista, erro) == true)
    {
        if (*erro != SUCESSO) // significa que a verificação se a lista está vazia não deu certo
        {
            return NULL;
        }
        return NULL;
    }

    ListaBloco *atual = lista->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->dado, dado) == 0)
        {
            *erro = SUCESSO;
            return atual;
        }
        atual = atual->prox;
    }
    *erro = SUCESSO;
    return NULL;
}

ListaBloco *lista_pop(Lista *lista, elem_lista *dado, tipo_erro *erro) /*, int *erro*/
{
    ListaBloco *p, *ant;

    if (lista->inicio == NULL || (strcmp(dado, lista->inicio->dado) < 0))
    { // verifica se a lista está vazia ou se o dado não está na lista
        *erro = ERRO_NULL;
        return NULL;
    }
    else if ((strcmp(dado, lista->inicio->dado) == 0))
    {
        p = lista->inicio;
        lista->inicio = lista->inicio->prox;
        free(p);
    }
    else
    {
        ant = NULL;
        p = lista->inicio;

        while ((p != NULL) && (strcmp(dado, p->dado) > 0))
        {
            ant = p;
            p = p->prox;
        }
        if ((p != NULL) && (strcmp(dado, p->dado) == 0))
        {
            ant->prox = p->prox;
            free(p);
        }
        else
        {
            *erro = ERRO_POP_VAZIO;
        }
    }
    return NULL;
}

bool lista_vazia(Lista *lista, tipo_erro *erro)
{
    if (lista == NULL)
    {
        *erro = ERRO_NULL;
        return true;
    }
    if (lista->inicio == NULL)
    {
        *erro = SUCESSO;
        return true;
    }
    *erro = SUCESSO;
    return false;
}

void lista_print(Lista *lista, tipo_erro *erro)
{
    if (lista == NULL)
    {
        *erro = ERRO_NULL;
        return;
    }
    if (lista_vazia(lista, erro) == true)
    {
        if (erro != SUCESSO) // significa que a verificação se a lista está vazia não deu certo
        {
            return;
        }
        *erro = ERRO_NULL; // tentou imprimir uma lista vazia
        return;
    }

    ListaBloco *atual = lista->inicio;
    while (atual != NULL)
    {
        printf("%s\n", atual->dado);
        atual = atual->prox;
    }
    *erro = SUCESSO;
}

void lista_libera(Lista *lista, tipo_erro *erro)
{
    if (lista == NULL)
    {
        *erro = ERRO_NULL;
        return;
    }
    if (lista_vazia(lista, erro) == true)
    {
        if (erro != SUCESSO) // significa que a verificação se a lista está vazia não deu certo
        {
            return;
        }
        *erro = ERRO_NULL; // tentou liberar uma lista vazia
        return;
    }

    ListaBloco *atual = lista->inicio;
    ListaBloco *proximo;
    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
    *erro = SUCESSO;
}

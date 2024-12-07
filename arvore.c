#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"

Arvore *arvore_init(tipo_erro *erro)
{
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    if (a == NULL)
    {
        *erro = ERRO_ALLOC;
    }
    else
    {
        a->raiz = NULL;
        a->totalNos = 0;
        a->Lista_Arv = lista_init(erro);
    }
    return a;
}

bool arvore_vazia(Arvore *a)
{
    if (a->raiz == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

no *arvore_busca(no *p, elem_chave *chave, tipo_erro *erro)
{
    if (p == NULL)
    {
        *erro = ERRO_NULL;
        return NULL;
    }
    else if (p->chave == *chave)
    {
        *erro = SUCESSO;
        return (p); // retorna o nó
    }
    else if (*chave < p->chave)
    {
        return (arvore_busca(p->esq, chave, erro));
    }
    else if (*chave > p->chave)
        return (arvore_busca(p->dir, chave, erro));
}

int alturaArvore(no *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    int alturaEsquerda = alturaArvore(raiz->esq);
    int alturaDireita = alturaArvore(raiz->dir);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
}

// lista _init do usuário na main
// lista_push adiciona o listabloco com o nome do filme e genero na lista,  na main
// lista_push adiciona o listabloco com o nome do filme e genero na lista geral,  na main

void arvore_inserir(Arvore *a, no **p, elem_arv *x, elem_chave *chave, Lista *l_ord, tipo_erro *erro)
{
    if (*p == NULL)
    {
        *p = (no *)malloc(sizeof(no));
        if (*p == NULL)
        {
            *erro = ERRO_NULL;
            return;
        }
        (*p)->chave = *chave;    // Define a chave do nó
        (*p)->dado = x;         // Define o dado associado à chave
        (*p)->dir = NULL;        // Inicializa o ponteiro para o filho à direita como NULL
        (*p)->esq = NULL;        // Inicializa o ponteiro para o filho à esquerda como NULL
        (*p)->lista_ord = l_ord; // Faz o ponteiro da lista do nó da árvore apontar para o ponteiro que foi passado por parâmetro

        *erro = SUCESSO;
        a->totalNos++; // Incrementa o número de total de nós da árvor
    }
    // Caso a chave já exista na árvore, definimos um erro
    else if ((*p)->chave == *chave)
    {
        *erro = ERRO_ELEM_REPETIDO; // Chave duplicada não permitida
        return;
    }
    // Se a chave for menor, percorremos o lado esquerdo da árvore
    else if (*chave < (*p)->chave)
    {
        arvore_inserir(a, &(*p)->esq, x, chave, l_ord, erro); // Recursão para o lado esquerdo
    }
    // Se a chave for maior, percorremos o lado direito da árvore
    else if (*chave > (*p)->chave)
    {
        arvore_inserir(a, &(*p)->dir, x, chave, l_ord, erro); // Recursão para o lado direito
    }
}

no *arvore_busca_maior(no **p, tipo_erro *erro)
{   
    if (*p == NULL)
    {
        *erro = ERRO_NULL;
        return NULL;
    }
    no *aux = *p;
    while (aux->dir != NULL)
        aux = aux->dir;
    return aux;
}

// antes de remover, precisa verificar lista geral de filmes
// liberar lista do usuario

void arvore_remover(Arvore *a, no **p, elem_chave *x, tipo_erro *erro)
{
    no *aux;
    if (*p == NULL)
        *erro = ERRO_NULL;
    else if (*x < (*p)->chave)
        return (arvore_remover(a, &(*p)->esq, x, erro));
    else if (*x > (*p)->chave)
        return (arvore_remover(a, &(*p)->dir, x, erro));
    else if (*x == (*p)->chave)
    {
        // caso 1: nó pai sem filhos
        if (((*p)->esq == NULL && (*p)->dir == NULL))
        {
            free(*p);
            *p = NULL;
            *erro = SUCESSO;
        }
        // caso 2:tem 1 filho
        else if ((*p)->esq == NULL)
        {
            aux = *p;
            *p = (*p)->dir;
            free(aux);
            *erro = SUCESSO;
        }
        else if ((*p)->dir == NULL)
        {
            aux = *p;
            *p = (*p)->esq;
            free(aux);
            *erro = SUCESSO;
        }
        // caso 3: tem 2 filhos
        else if (((*p)->esq != NULL && (*p)->dir != NULL))
        {
            no *aux2 = arvore_busca_maior(&(*p)->esq, erro);
            (*p)->chave = aux2->chave; // só o numero usp, precisa trocar outras inform
            (*p)->dado = aux2->dado;
            (*p)->maiorDiferencaAltura = aux2->maiorDiferencaAltura;
            (*p)->lista_ord = aux2->lista_ord;

            return (arvore_remover(a, &(*p)->esq, &(*p)->chave, erro));
        }
        a->totalNos--;
    }
}

void arvore_libera(no *raiz, tipo_erro *erro) {
    if (raiz == NULL) {
        *erro = ERRO_NULL; // Indica que a raiz é nula
        return;
    }

    // Inicializa o erro como sucesso
    *erro = SUCESSO;

    // Libera a lista ordenada associada à subárvore esquerda, se existir
    if (raiz->esq != NULL && raiz->esq->lista_ord != NULL) {
        lista_libera(raiz->esq->lista_ord, erro);
        if (*erro != SUCESSO) {
            return; // Interrompe se ocorrer erro
        }
    }

    // Libera a lista ordenada associada à subárvore direita, se existir
    if (raiz->dir != NULL && raiz->dir->lista_ord != NULL) {
        lista_libera(raiz->dir->lista_ord, erro);
        if (*erro != SUCESSO) {
            return; // Interrompe se ocorrer erro
        }
    }

    // Libera recursivamente as subárvores
    arvore_libera(raiz->esq, erro);
    if (*erro != SUCESSO) {
        return; // Interrompe se ocorrer erro
    }

    arvore_libera(raiz->dir, erro);
    if (*erro != SUCESSO) {
        return; // Interrompe se ocorrer erro
    }

    // Libera o nó atual
    free(raiz);
}

// colocar no arquivo vai ser feito na main

void arvore_print(no *raiz, tipo_erro *erro)
{

    if (raiz == NULL)
    {
        *erro = ERRO_NULL; // Se o nó atual for nulo, simplesmente retorna
        return;
    }

    // Percorre a subárvore esquerda
    arvore_print(raiz->esq, erro);

    // Imprime o valor do nó atual
    printf("%d ", raiz->chave);
    printf("\n");

    // Percorre a subárvore direita
    arvore_print(raiz->dir, erro);
}
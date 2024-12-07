#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"


Arvore *arvore_init(tipo_erro *erro){
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    if (a == NULL){
        *erro = ERRO_ALLOC;
    }else{
        a->raiz =NULL;
        a->altura = 0;
        a->totalNos = 0;
        a->Lista_Arv = NULL;
    }
    return a;
}


bool arvore_vazia(Arvore *a, tipo_erro *erro){
    if (a->raiz == NULL)
    {
        *erro = ERRO_NULL;
        return true;
    }
    else
        *erro = SUCESSO;
        return false;
}


no *arvore_busca(no *p, elem_chave *chave, tipo_erro *erro){
    if (p == NULL){
        *erro = ERRO_NULL;
        return NULL;
    }
    else if (p->chave == *chave)
    {
        *erro = SUCESSO;
        return (p); //retorna o nó        
    }
    else if (*chave < p->chave)
    {
        return (arvore_busca(p->esq, chave, erro));
    }
    else if (*chave > p->chave)
        return (arvore_busca(p->dir, chave, erro));
}

void arvore_inserir(Arvore *a, no **p, elem_arv *x, elem_chave *chave, tipo_erro *erro) {   
    
    if (*p == NULL)
    {
        *p = (no *)malloc(sizeof(no));
        if (*p == NULL) {
            *erro = ERRO_NULL; 
            return;
        }
        (*p)->chave = *chave; // Define a chave do nó
        (*p)->dado = *x;      // Define o dado associado à chave
        (*p)->dir = NULL;     // Inicializa o ponteiro para o filho à direita como NULL
        (*p)->esq = NULL;     // Inicializa o ponteiro para o filho à esquerda como NULL
        
        *erro = SUCESSO; 
        a->totalNos++;     
    }
    // Caso a chave já exista na árvore, definimos um erro
    else if ((*p)->chave == *chave) {
        *erro = ERRO_ELEM_REPETIDO; // Chave duplicada não permitida
        return;
    }
    // Se a chave for menor, percorremos o lado esquerdo da árvore
    else if (*chave < (*p)->chave) {
        arvore_inserir(a,&(*p)->esq, x, chave, erro); // Recursão para o lado esquerdo
    }
    // Se a chave for maior, percorremos o lado direito da árvore
    else if (*chave > (*p)->chave) {
        arvore_inserir(a,&(*p)->dir, x, chave, erro); // Recursão para o lado direito
    }

    //calcula altura e atualiza altua
}


no* arvore_busca_maior(no **p)
{
    no *aux = *p;
    while (aux->dir != NULL)
        aux = aux->dir;
    return aux;
}

void arvore_remover(Arvore *a, no **p, elem_chave *x, tipo_erro *erro){
    no *aux;
    if (*p == NULL)
        *erro = ERRO_NULL;
    else if (*x < (*p)->chave)
        return (arvore_remover(a,&(*p)->esq, x, erro));
    else if (*x > (*p)->chave)
        return (arvore_remover(a,&(*p)->dir, x, erro));
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
            no *aux2 = arvore_busca_maior(&(*p)->esq);
            (*p)->chave = aux2->chave; //só o numero usp, precisa trocar outras inform
            (*p)->dado = aux2->dado;
            (*p)->maiorDiferencaAltura =aux2->maiorDiferencaAltura;
            (*p)->lista_ord = aux2->lista_ord;
            
            return (arvore_remover(a, &(*p)->esq, &(*p)->chave, erro));
        }
        a->totalNos--; 
    }

}

void arvore_libera(Arvore *a, tipo_erro *erro){

}

void arvore_print(Arvore *a, tipo_erro *erro){

}
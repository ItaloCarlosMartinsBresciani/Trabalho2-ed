#ifndef arvore_h
#include "lista.h"

#define TAMN 50

typedef char elem_arv;
typedef int elem_chave;

typedef struct no {
    elem_arv *dado; 
    elem_chave chave; // chave de busca
    Lista *lista_ord; // Lista ordenada
    struct no *esq, *dir; // Sub-árvores esquerda e direita
    //int maiorDiferencaAltura;
} no;

// Estrutura para armazenar dados da árvore
typedef struct Arvore {
    int totalNos; // Total de nós da árvore
    Lista *Lista_Arv; //lista ligada à árvore
    no *raiz;
}Arvore;

// Inicializar árvore
Arvore *arvore_init(tipo_erro *erro);
// Verificar se a árvore está vazia
bool arvore_vazia(Arvore *a);
// Verificar se há um elemento na árvore pela chave
no* arvore_busca(no *p, elem_chave *chave, tipo_erro *erro);
// Inserir elemento da árvore
void arvore_inserir(Arvore *a, no **p, elem_arv *x, elem_chave *chave, Lista *l_ord, tipo_erro *erro);
// Remover elemento da árvore
void arvore_remover(Arvore *a, no **p, elem_chave *x, tipo_erro *erro);
// Liberar memória alocada
void arvore_libera(no *raiz, tipo_erro *erro);
// Imprimir árvore
void arvore_print(no *raiz, tipo_erro *erro);

no* arvore_busca_maior(no **p, tipo_erro *erro);

int alturaArvore(no *raiz);


#endif
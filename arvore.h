#ifndef arvore_h
#include "lista.h"

#define TAMN 50

typedef char elem_arv;
typedef int elem_chave;

typedef struct no {
    elem_arv *dado; 
    elem_chave chave; // chave de busca
    // quando o coeficiente é >= |1|, a árvore está desbalanceada
    ListaBloco *lista_ord; // Lista ordenada
    struct no *esq, *dir; // Sub-árvores esquerda e direita
    int maiorDiferencaAltura;
} no;

// Estrutura para armazenar estatísticas da árvore
typedef struct Arvore {
    int totalNos;
    int altura;
    ListaBloco *Lista_Arv; //lista ligada à árvore
    no *raiz;
}Arvore;

// Inicializar árvore
Arvore *arvore_init(tipo_erro *erro);
// Verificar se a árvore está vazia
bool arvore_vazia(Arvore *a, tipo_erro *erro);
// Verificar se há um elemento na árvore pela chave
no* arvore_busca(no *p, elem_chave *x, tipo_erro *erro);
// Inserir elemento da árvore
void arvore_inserir(Arvore *a,no **p, elem_arv *x, elem_chave *chave, tipo_erro *erro);
// Remover elemento da árvore
void arvore_remover(Arvore *a,no **p, elem_chave *x, tipo_erro *erro);
// Liberar memória alocada
void arvore_libera(Arvore *a, tipo_erro *erro);
// Imprimir árvore
void arvore_print(Arvore *a, tipo_erro *erro);

no* arvore_busca_maior(no **p, tipo_erro *erro);


#endif
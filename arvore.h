#ifndef arvore_h
#include "lista.h"

#define TAMN 50

typedef struct Aluno {
    char nome[TAMN];
    int numeroUSP;
    int coeficeinte_balanceamento;
    ListaBloco *filmes; // Lista ordenada de filmes
    struct Aluno *esq, *dir; // Sub-árvores esquerda e direita
    int maiorDiferencaAltura;
} Aluno;

// Estrutura para armazenar estatísticas da árvore
typedef struct DadosArvore {
    int totalNos;
    int altura;
    ListaBloco *Geral;
    Aluno *raiz;
} DadosArvore;

#endif
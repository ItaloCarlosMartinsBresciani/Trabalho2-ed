#ifndef LISTA_H
#define LISTA_H

// Inclusão de bibliotecas
#include <stdbool.h>
#include "erro.h"

// Define o tipo "elem_lista" como char
typedef char elem_lista;
typedef int tipo_do_bloco;

#define QUANT 8 // definida a quantidade de tipos que cada bloco pode assumir
// No caso dos filmes: {1- Ação, 2- Aventura, 3- Comedia, 4 - Drama, 5- Ficcao, 6- Romance, 7- Suspense, 8 - Terror}

typedef struct listabloco
{
    elem_lista *dado;   
    tipo_do_bloco tipo; 
    int cont_ref;      
    struct listabloco *prox, *ant;
} ListaBloco;

typedef struct lista
{
    ListaBloco *inicio;
    //ListaBloco *fim;
    int vetor[QUANT]; // vetor que armazena as quantidades de filmes cadastrados por genero
} Lista;

//  Inicializar uma nova lista
Lista *lista_init(tipo_erro *erro);

//  Adicionar um novo elemento na lista
void lista_push(Lista *lista, elem_lista *dado, tipo_do_bloco *tipo, tipo_erro *erro);

//  Remover e retornar o bloco do fim da lista
ListaBloco *lista_pop(Lista *lista, elem_lista *dado, tipo_erro *erro);

//  Verificar se a lista está vazia
bool lista_vazia(Lista *lista, tipo_erro *erro); // erro implementado até aqui

//  Imprimir os elementos da lista
void lista_print(Lista *lista, tipo_erro *erro); // erro implement até aqui

//  Liberar a memória ocupada pela lista
void lista_libera(Lista *lista, tipo_erro *erro); // erro implement

//  Verificar se um elemento tá presente na lista
ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado, tipo_erro *erro);


#endif
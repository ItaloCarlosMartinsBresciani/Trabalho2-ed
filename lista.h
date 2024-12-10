#ifndef LISTA_H
#define LISTA_H

// Inclusão de bibliotecas
#include <stdbool.h>
#include "erro.h"


typedef char elem_lista;
typedef int tipo_do_bloco;

#define QUANT 8 

typedef struct listabloco
{
    elem_lista *dado;   
    tipo_do_bloco tipo; 
    tipo_do_bloco cont_ref;    
    struct listabloco *prox, *ant;
} ListaBloco;

typedef struct lista
{
    ListaBloco *inicio;
    int vetor[QUANT];    
                        
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
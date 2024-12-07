#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"

int main()
{
    tipo_erro erro;
    Arvore *a = arvore_init(&erro);


    ////////////////////////////////////////////////////////////
    Lista *lista1 = lista_init(&erro);

    
    elem_arv nome[100] = "Ana";

    elem_arv *dado = (elem_arv *)malloc(strlen(nome) + 1);
    if (dado == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado, nome);
    elem_chave chave1 = 1; 
    


    arvore_inserir(a, &a->raiz, dado, &chave1, lista1, &erro);
    printf("----------------------\n");
    arvore_print(a->raiz, &erro);
    printf("----------------------\n");
    ////////////////////////////////////////////////////////////

    Lista *lista2 = lista_init(&erro);
    elem_arv nome2[100] = "Luiz";
    elem_arv *dado2 = (elem_arv *)malloc(strlen(nome2) + 1);
    if (dado2 == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado2, nome2);
    elem_chave chave2 = 2; 
    arvore_inserir(a, &a->raiz, dado2, &chave2, lista2, &erro);
    printf("----------------------\n");
    arvore_print(a->raiz, &erro);
    printf("----------------------\n");
    
    /////////////////////////////////////////////////////////////
    

    
    

    arvore_remover(a, &a->raiz, &chave1, &erro);
    printf("----------------------\n");
    arvore_print(a->raiz, &erro);
    printf("----------------------\n");



///////////////////////////////////////////


    Lista *lista3 = lista_init(&erro);
    elem_arv nome3[100] = "Solrac";
    elem_arv *dado3 = (elem_arv *)malloc(strlen(nome3) + 1);
    if (dado3 == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado3, nome3);
    elem_chave chave3 = 3; 
    arvore_inserir(a, &a->raiz, dado3, &chave3, lista3, &erro);
    printf("----------------------\n");
    arvore_print(a->raiz, &erro);
    printf("----------------------\n");



///////////////////////////////////////////////////
    Lista *lista5 = lista_init(&erro);

    
    elem_arv nome5[100] = "bANANINHA";

    elem_arv *dado5 = (elem_arv *)malloc(strlen(nome5) + 1);
    if (dado5 == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado5, nome5);
    elem_chave chave5 = 5; 
    


    arvore_inserir(a, &a->raiz, dado5, &chave5, lista5, &erro);
    printf("----------------------\n");
    arvore_print(a->raiz, &erro);
    printf("----------------------\n");
    ///////////////////////////////////////////////


    arvore_remover(a, &a->raiz, &chave3, &erro); ///REMOVE SOLRAC (╯︵╰,) o(╥﹏╥)o
    printf("----------------------\n");
    arvore_print(a->raiz, &erro);
    printf("----------------------\n");




    arvore_libera(a->raiz, &erro);


    return 0;
}


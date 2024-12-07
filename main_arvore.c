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
    elem_arv filme[100] = "Velozes e Furiosos";
    elem_arv *dado = (elem_arv *)malloc(strlen(filme) + 1);
    if (dado == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado, filme);
    elem_chave chave = 1; //genero
    arvore_inserir(&a->raiz, dado, &chave, &erro);
    printf("----------------------\n");
    arvore_print(a, &erro);
    printf("----------------------\n");

    elem_arv filme2[100] = "Vingadores";
    elem_arv *dado2 = (elem_arv *)malloc(strlen(filme2) + 1);
    if (dado2 == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado2, filme2);
    elem_chave chave2 = 1; //genero
    arvore_inserir(&a->raiz, dado2, &chave2, &erro);
    printf("----------------------\n");
    arvore_print(a, &erro);
    printf("----------------------\n");
    arvore_remover(&a->raiz, &chave2, &erro);
    printf("----------------------\n");
    arvore_print(a, &erro);
    printf("----------------------\n");
    arvore_libera(a, &erro);


    return 0;
}


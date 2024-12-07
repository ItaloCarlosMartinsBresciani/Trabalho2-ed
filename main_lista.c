#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "erro.h"

int main()
{
    tipo_erro erro;
    Lista *lista = lista_init(&erro);
    elem_lista filme[100] = "Velozes e Furiosos";
    elem_lista *dado = (elem_lista *)malloc(strlen(filme) + 1);
    if (dado == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;   
    }
    strcpy(dado, filme);
    tipo_do_bloco tipo = 1; //genero
    
    
    lista_push(lista, dado, &tipo, &erro);
    printf("----------------------\n");
    lista_print(lista, &erro);
    printf("----------------------\n");

    elem_lista filme2[100] = "Vingadores";
    elem_lista *dado2 = (elem_lista *)malloc(strlen(filme2) + 1);
    if (dado2 == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    strcpy(dado2, filme2);
    tipo_do_bloco tipo2 = 1; //genero
    lista_push(lista, dado2, &tipo2, &erro);
    printf("----------------------\n");
    lista_print(lista, &erro);
    printf("----------------------\n");
    lista_pop(lista, dado2, &erro);
    printf("----------------------\n");
    lista_print(lista, &erro);
    printf("----------------------\n");
    lista_libera(lista, &erro);
    return 0;
}


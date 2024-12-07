// erro.h - Definição dos tipos de erro

#ifndef ERRO_H
#define ERRO_H

typedef enum{
    SUCESSO, // Operação executada com sucesso (0)
    ERRO_ALLOC, // Erro de alocação de memória (1)
    ERRO_NULL, // Tentativa de uso de um ponteiro ou dado nulo (2)
    ERRO_ELEM_REPETIDO, // Tentativa de inserção de elemento repetido (3)
    ERRO_POP_VAZIO, // Tentativa de retirar elemento em uma estrutura vazia (4)
    ERRO_DEALLOC // Erro ao desalocar memória (5)
}tipo_erro;

#endif // ERRO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"
#include "main_funcoes.h"


int main() {
    int opcao;

    do {
        exibir_menu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                criar_cadastro();
                break;
            case 2:
                listar_alunos();
                break;
            case 3:
                buscar_usuario();
                break;
            case 4:
                listar_filmes();
                break;
            case 5:
                buscar_filme();
                break;
            case 6:
                recomendar_colega();
                break;
            case 7:
                recomendar_oposto();
                break;
            case 8:
                exportar_dados();
                break;
            case 9:
                exibir_dados_arvore();
                break;
            case 10:
                remover_usuario();
                break;
            case 11:
                funcionalidade_extra();
                break;
            case 0:
                printf("\nSaindo do sistema. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
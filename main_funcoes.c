#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"
#include "main_funcoes.h"


void criar_cadastro();
void listar_alunos();
void buscar_usuario();
void listar_filmes();
void buscar_filme();
void recomendar_colega();
void recomendar_oposto();
void exportar_dados();
void exibir_dados_arvore();
void remover_usuario();
void funcionalidade_extra();

void exibir_menu() {
    printf("\n==============================\n");
    printf("    SISTEMA DO CINE USP     \n");
    printf("==============================\n");
    printf("1) Criar um cadastro\n");
    printf("2) Listar todos os alunos cadastrados\n");
    printf("3) Buscar um usuário no sistema\n");
    printf("4) Listar filmes diferentes em ordem alfabética\n");
    printf("5) Buscar um filme no sistema\n");
    printf("6) Recomendar colega para cinema\n");
    printf("7) Recomendar colega com perfil oposto\n");
    printf("8) Exportar dados para arquivo texto\n");
    printf("9) Exibir dados técnicos da árvore\n");
    printf("10) Remover usuário do cadastro\n");
    printf("11) Funcionalidade extra (a ser definida)\n");
    printf("0) Sair\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}
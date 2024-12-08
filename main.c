#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"
#include "main_funcoes.h"

int main()
{
  // Inicilizando as estruturas que serão usadas no sistema
  tipo_erro erro = SUCESSO;
  Arvore *arv_sistema = arvore_init(&erro);

  int opcao;

  do
  {
    exibir_menu();
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer do teclado

    switch (opcao)
    {
    case 1:
      criar_cadastro(arv_sistema, &erro);
      if (erro == SUCESSO)
      {
        printf("Cadastro do usuário realizado com sucesso!\n");
      }
      else
      {
        printf("Erro ao cadastrar usuário.\n");
      }
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 2:
      if (arvore_vazia(arv_sistema))
      {
        printf("Não há usuários cadastrados no sistema");
        break;
      }
      printf("\n---LISTAGEM DE ALUNOS---\n");
      listar_alunos(arv_sistema->raiz, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 3: // busca um usuário específico no sistema e fala se ele está ou não cadastrado
      buscar_usuario(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 4: // lista todos os filmes cadastrados no sistema
      listar_filmes(arv_sistema->Lista_Arv, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 5: // busca um filme e verifica quantas vezes foi mencionado
      buscar_filme(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 6:
      recomendar_colega(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 7:
      recomendar_colega_oposto(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 8:
      exportar_dados(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 9:
      exibir_dados_arvore(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 10:
      remover_usuario(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;
    case 11: // Informa qual é o filme mais mencionado pelos alunos
      mais_mencionado(arv_sistema->Lista_Arv, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;
    case 12: // cadastrar filmes
      cadastrar_filmes(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();

    case 0:
      printf("\nSaindo do sistema. Até mais!\n");
      break;

    default:
      printf("\nOpção inválida! Tente novamente.\n");
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
    }
  } while (opcao != 0);

  arvore_libera(arv_sistema->raiz, &erro);
  if (erro != SUCESSO)
  {
    printf("Erro ao liberar memória do sistema!\n");
  }
  else
  {
    printf("Sistema liberado com sucesso! Encerrando..\n");
  }

  return 0;
}
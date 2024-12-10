#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "erro.h"
#include "main_funcoes.h"
#include <locale.h>

int main()
{
  setlocale(LC_ALL, "Portuguese");
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
    case 1: // cadastra um novo usuário no sistema
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

    case 2: // lista todos os usuários cadastrados no sistema
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

    case 6: // recomenda um colega com base na similaridade de gostos
      recomendar_colega(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 7:  // recomenda um colega com base na diferença de gostos
      recomendar_colega_oposto(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 8: // exporta os dados para um arquivo texto
      exportar_dados(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 9: // exibe dados técnicos da árvore
      exibir_dados_arvore(arv_sistema, &erro);
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
      break;

    case 10: // remove um usuário do sistema
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
      break;

    case 0: // sair do sistema
      printf("\nSaindo do sistema. Até mais!\n");
      break;

    default: // opção inválida
      printf("\nOpção inválida! Tente novamente.\n");
      printf("Aperte uma tecla para continuar!");
      getchar();
      limpar_tela();
    }
  } while (opcao != 0);
  // Liberando a memória alocada para a árvore
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
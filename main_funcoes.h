#ifndef MAIN_FUNCOES_H
#define MAIN_FUNCOES_H



void criar_cadastro(Arvore *arv_sist, tipo_erro *erro);
void listar_alunos(no *raiz, tipo_erro *erro);
void buscar_usuario(Arvore *arv_sist, tipo_erro *erro);
void listar_filmes(Lista *lista_arv, tipo_erro *erro);
void buscar_filme(Arvore *arv_sist, tipo_erro *erro);
void recomendar_colega(Arvore *arv_sist, tipo_erro *erro);
void percorrer_arvore(no *raiz, int *vetor_ref, int *menor_distancia, no **mais_proximo, no *usuario_atual);
void percorrer_arvore_oposto(no *raiz, int *vetor_ref, int *maior_distancia, no **menos_proximo, no *usuario_atual);
void recomendar_colega_oposto(Arvore *arv_sist, tipo_erro *erro);
//void exportar_dados();
void exibir_dados_arvore(Arvore *arv_sist, tipo_erro *erro);
void remover_usuario(Arvore *arv_sist, tipo_erro *erro);
void mais_mencionado(Lista *lista_arv, tipo_erro *erro);
void auxiliar_cadastro(Arvore *arv_sist, Lista *l_ord, tipo_erro *erro);
void exibir_menu();
void limpar_tela();
void cadastrar_filmes(Arvore *arv_sistema, tipo_erro *erro);


#endif
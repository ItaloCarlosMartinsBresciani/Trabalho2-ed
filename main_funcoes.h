#ifndef MAIN_FUNCOES_H
#define MAIN_FUNCOES_H



void criar_cadastro(Arvore *arv_sist, tipo_erro *erro);
void listar_alunos(no *raiz, tipo_erro *erro);
void buscar_usuario(Arvore *arv_sist, tipo_erro *erro);
void listar_filmes(Lista *lista_arv, tipo_erro *erro);
void buscar_filme(Arvore *arv_sist, tipo_erro *erro);
void recomendar_colega(Arvore *arv_sist, tipo_erro *erro);
//void recomendar_oposto();
//void exportar_dados();
//void exibir_dados_arvore();
//void remover_usuario();
void mais_mencionado(Lista *lista_arv, tipo_erro *erro);
void exibir_menu();
void limpar_tela();


#endif
#ifndef MAIN_FUNCOES_H
#define MAIN_FUNCOES_H

// Função que adiciona um filme na lista geral
void add_lista_geral(Arvore *arv_sist, elem_arv *filme, tipo_do_bloco *genero, tipo_erro *erro); 
void arquivo_listar_alunos(no *raiz, FILE *arquivo, tipo_erro *erro);
// Função auxiliar para o cadastro
void auxiliar_cadastro(Arvore *arv_sist, Lista *l_ord, tipo_erro *erro); 
// Função que busca um filme
void buscar_filme(Arvore *arv_sist, tipo_erro *erro); 
// Função que busca um usuário
void buscar_usuario(Arvore *arv_sist, tipo_erro *erro); 
// Função que calcula a distância euclidiana
int calcular_distancia_euclidiana(int *vetor1, int *vetor2); 
// Função que cadastra filmes
void cadastrar_filmes(Arvore *arv_sistema, tipo_erro *erro); 
// Função que cria um cadastro
void criar_cadastro(Arvore *arv_sist, tipo_erro *erro);
// Função que exibe os dados técnicos da árvore
void exibir_dados_arvore(Arvore *arv_sist, tipo_erro *erro); 
// Função que exibe o menu
void exibir_menu(); 
// Função que exporta os dados para um arquivo texto
void exportar_dados(Arvore *arv_sist, tipo_erro *erro);
// Função que limpa a tela
void limpar_tela(); 
// Função que lista os alunos
void listar_alunos(no *raiz, tipo_erro *erro); 
// Função que lista os filmes
void listar_filmes(Lista *lista_arv, tipo_erro *erro); 
// Função que informa qual é o filme mais mencionado
void mais_mencionado(Lista *lista_arv, tipo_erro *erro); 
// Função que percorre a árvore para o colega simnilar
void percorrer_arvore(no *raiz, int *vetor_ref, int *menor_distancia, no **mais_proximo, no *usuario_atual); 
// Função que percorre a árvore para o colega oposto
void percorrer_arvore_oposto(no *raiz, int *vetor_ref, int *maior_distancia, no **menos_proximo, no *usuario_atual); 
// Função que recomenda um colega
void recomendar_colega(Arvore *arv_sist, tipo_erro *erro); 
// Função que recomenda um colega oposto
void recomendar_colega_oposto(Arvore *arv_sist, tipo_erro *erro);
// Função que remove um usuário
void remover_usuario(Arvore *arv_sist, tipo_erro *erro); 


#endif
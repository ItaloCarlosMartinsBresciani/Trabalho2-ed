#ifndef lista_h

// #define Suspense 1
// #define Acao 2
// #define Comedia 3
// #define Terror 4
// #define Romance 5
// #define Drama 6
// #define Ficcao 7
// #define Aventura 8

#define TAMF 100
#define QUANTGENERO 9 //{1- Ação, 2- Aventura, 3- Comedia, 4 - Drama, 5- Ficcao, 6- Romance, 7- Suspense, 8 - Terror}

typedef struct Filme{
    char nome[TAMF];
    int cont_ref; //contagem de referencias para a lista geral de filmes
    struct Filme *prox;
} Filme;


typedef struct ListaFilmes {
    Filme *inicio;
    int genero[QUANTGENERO]; //vetor com quantidade de filmes de cada generos 
} ListaFilmes;



//void destruirLista(ListaFilmes *lista);
//  Inicializar uma nova lista de filmes

#endif
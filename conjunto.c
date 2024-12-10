#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

struct conjunto
{
    int ed; // Tipo da estrutura de dado: 0 = AVL e 1 = Árvore Rubro-Negra
    void *estrutura; // Ponteiro void genérico, para poder apontar para ambas as estruturas 
    int tam; // Tamanho do conjunto
};

CONJ *conjunto_criar(int ed){ // Cria um conjunto e define o tipo de ponteiro, coloca o tamanho em 0 e retorna o conjunto

    CONJ *conjunto = (CONJ*) malloc(sizeof(CONJ));

    if(conjunto != NULL){

        conjunto->ed = ed;
        conjunto->tam = 0;

        if(ed == 0)
            conjunto->estrutura = arvore_avl_criar();

        else 
            conjunto->estrutura = arvore_rn_criar();
        
    }

    return conjunto;
}

bool conjunto_pertence(CONJ *A, int elemento){ // Checa se um elemento pertence ao conjunto, realizando uma busca na estrutura de dados escolhida

    if(A != NULL){

        if(A->ed == 0)
            return(arvore_avl_busca(A->estrutura, elemento));

        else   
            return(arvore_rn_busca(A->estrutura, elemento));

    }

    return false;

}

bool conjunto_inserir(CONJ *s, int elemento){ // Insere um elemento na estrutura de dados escolhida

    if(s != NULL){

        s->tam++;

        if(s->ed == 0)
            return(arvore_avl_inserir(s->estrutura, elemento));

        else
            return(arvore_rn_inserir(s->estrutura, elemento));

    }

    return false;
            
}

bool conjunto_remover(CONJ *s, int elemento){ // Busca e remove um elemento da estrutura de dados escolhida
    
    if(s != NULL){

        s->tam--;

        if(s->ed == 0)
            return(arvore_avl_remover(s->estrutura, elemento));

        else
            return(arvore_rn_remover(s->estrutura, elemento));

    }

    return false;

}

void conjunto_apagar(CONJ **s){ // Apaga o conjunto escolhido

    if((*s) != NULL){

        if((*s)->ed == 0)
            arvore_avl_apagar((AVL **)&(*s)->estrutura);

        else   
            arvore_rn_apagar((ARN **)&(*s)->estrutura);

    (*s)->tam = 0;

    (*s)->estrutura = NULL;
    (*s) = NULL;

    }
    
}

void conjunto_imprimir(CONJ *s){ // Imprime o conjunto em ordem crescente, realizando uma visita em ordem dos nós
    
    if(s != NULL){

        if(s->ed == 0)
            arvore_avl_imprimir(s->estrutura);

        else
            arvore_rn_imprimir(s->estrutura);

    }
}

CONJ *conjunto_uniao(CONJ *A, CONJ *B){ // Retorna um conjunto C, que é a união dos conjuntos A e B

    if(A == NULL || B == NULL) 
        return NULL;

    CONJ *C = conjunto_criar(A->ed);

    if(A->ed == 0){
            
        arvore_avl_copiar(A->estrutura, C->estrutura); // Copia a maior árvore em uma terceira árvore
        arvore_avl_uniao(C->estrutura, B->estrutura); // Insere os elementos do conjunto B que não estão no conjunto A, no conjunto C

    }

    else{

        arvore_rn_copiar(A->estrutura, C->estrutura);
        arvore_rn_uniao(C->estrutura, B->estrutura);

    }

    return C;

    }

CONJ *conjunto_intersecao(CONJ *A, CONJ *B){ // Retorna um conjunto C, que é a interseção dos conjuntos A e B

    if(A == NULL || B == NULL) 
        return NULL;

    CONJ *C = conjunto_criar(A->ed);

    if(A->ed == 0){

        if(A->tam > B->tam) 
            arvore_avl_intersecao(A->estrutura, B->estrutura, C->estrutura);

        else 
            arvore_avl_intersecao(B->estrutura, A->estrutura, C->estrutura);

    }

    else{

        if(A->tam > B->tam)
            arvore_rn_intersecao(A->estrutura, B->estrutura, C->estrutura);

        else
            arvore_rn_intersecao(B->estrutura, A->estrutura, C->estrutura);

    }


    return C;

}


#ifndef CONJUNTO_H
    #define CONJUNTO_H

    #include "avl.h"
    #include "arn.h"
    #include "stdbool.h"

    typedef struct conjunto CONJ;

CONJ *conjunto_criar(int ed);
bool conjunto_pertence(CONJ *A, int elemento);
bool conjunto_inserir (CONJ *s, int elemento);
bool conjunto_remover(CONJ *s, int elemento);
void conjunto_apagar(CONJ **s);
void conjunto_imprimir(CONJ *s);
CONJ *conjunto_uniao(CONJ *A, CONJ *B);
CONJ *conjunto_intersecao(CONJ *A, CONJ *B);

#endif
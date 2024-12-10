#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

int main(){

    CONJ *A, *B;
    int tipoed, a_tam, b_tam, elemento, operacao;

    scanf("%d", &tipoed);

    A = conjunto_criar(tipoed);
    B = conjunto_criar(tipoed);

    scanf("%d", &a_tam);

    scanf("%d", &b_tam);

    for(int i = 0; i < a_tam; i++){

        scanf("%d", &elemento);
        conjunto_inserir(A, elemento);

    }

    for(int i = 0; i < b_tam; i++){

        scanf("%d", &elemento);
        conjunto_inserir(B, elemento);

    }

    scanf("%d", &operacao);

    if (operacao == 1){

        CONJ *C = conjunto_criar(tipoed);

        C = conjunto_intersecao(A, B);


        conjunto_imprimir(C);

        conjunto_apagar(&C);

    }

    if (operacao == 2){

        CONJ *C = conjunto_criar(tipoed);

        C = conjunto_uniao(A, B);

        conjunto_imprimir(C);
        printf("\n");

        conjunto_apagar(&C);

    }

    if (operacao == 3){

        scanf("%d", &elemento);

        if(conjunto_pertence(A, elemento))
            printf("Pertence.");

        else
            printf("Nao Pertence.");

    }

    if (operacao == 4){

        scanf("%d", &elemento);

        if(conjunto_pertence(A, elemento))
            conjunto_remover(A, elemento);

        else
            printf("Elemento nao encontrado.");

        conjunto_imprimir(A);
        

    }

    if(operacao < 1 || operacao > 4)
        printf("Operacao Invalida");
        
    conjunto_apagar(&A);
    conjunto_apagar(&B);

    return 0;

}

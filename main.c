#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

int main(){

    CONJ *A, *B;
    int tipoed, a_tam, b_tam, elemento, operacao;

    printf("Digite as estrutura de dados que será utilizada: \n");
    printf("0 - Árvore AVL\n");
    printf("1 - Árvore Rubro-Negra\n");
    printf("\n");

    scanf("%d", &tipoed);

    A = conjunto_criar(tipoed);
    B = conjunto_criar(tipoed);

    printf("Digite o tamanho do conjunto A: \n");
    scanf("%d", &a_tam);

    printf("Digite o tamanho do conjunto B: \n");
    scanf("%d", &b_tam);

    printf("\n");

    printf("Insira os %d elementos do conjunto A: \n", a_tam);

    for(int i = 0; i < a_tam; i++){

        scanf("%d", &elemento);
        conjunto_inserir(A, elemento);

    }

    printf("Insira os %d elementos do conjunto B: \n", b_tam);

    for(int i = 0; i < b_tam; i++){

        scanf("%d", &elemento);
        conjunto_inserir(B, elemento);

    }

    printf("Digite a operação que será feita: \n");
    printf("1 - Interseção entre os dois conjuntos\n");
    printf("2 - União dos dois conjuntos\n");
    printf("3 - Conferir se um elemento pertence ao conjunto A\n");
    printf("4 - Remover um elemento do conjunto A\n");
    printf("\n"); 

    scanf("%d", &operacao);

    if (operacao == 1){

        CONJ *C = conjunto_criar(tipoed);

        C = conjunto_intersecao(A, B);

        printf("A interseção entre os conjuntos A e B é: ");
        conjunto_imprimir(C);

    }

    if (operacao == 2){

        CONJ *C = conjunto_criar(tipoed);

        C = conjunto_uniao(A, B);

        printf("A união dos conjuntos A e B é: ");
        conjunto_imprimir(C);
        printf("\n");

    }

    if (operacao == 3){

        printf("Digite o elemento: \n");

        scanf("%d", &elemento);

        if(conjunto_pertence(A, elemento))
            printf("Pertence\n");

        else
            printf("Nao Pertence\n");

    }

    if (operacao == 4){

        printf("Digite o elemento: \n");

        scanf("%d", &elemento);

        if(conjunto_pertence(A, elemento)){

            conjunto_remover(A, elemento);
            
            printf("Conjunto A sem o elemento %d: ", elemento);
            conjunto_imprimir(A);

        }

        else
            printf("Elemento %d não encontrado no conjunto A\n", elemento);

    }

    if (operacao > 4 || operacao < 1)
        printf("Operação Inválida");
        

    return 0;

}
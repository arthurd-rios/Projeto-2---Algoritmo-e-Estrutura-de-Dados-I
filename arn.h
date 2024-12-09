#ifndef _ARVORE_RN_H
#define _ARVORE_RN_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct arn ARN;

ARN *arvore_rn_criar(); 
bool arvore_rn_inserir(ARN *T, int chave);
void arvore_rn_imprimir(ARN *T);
void arvore_rn_apagar(ARN **T);
bool arvore_rn_remover(ARN *T, int chave);  
bool arvore_rn_busca(ARN *T, int chave);
bool arvore_rn_vazia(ARN *T);
void arvore_rn_copiar(ARN *T1, ARN *T2);
void arvore_rn_uniao(ARN *T1, ARN *T2);
void arvore_rn_intersecao(ARN *T1, ARN *T2, ARN *T3);

#endif
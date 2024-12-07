#ifndef _ARVORE_AVL_H
#define _ARVORE_AVL_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct avl AVL;

AVL *arvore_avl_criar (); 
bool arvore_avl_inserir (AVL *T, int chave);
void arvore_avl_imprimir (AVL *T);
void arvore_avl_apagar (AVL **T);
bool arvore_avl_remover(AVL *T, int chave);  
bool arvore_avl_busca(AVL *T, int chave);
bool arvore_avl_vazia(AVL *T);
void arvore_avl_copiar(AVL *T1, AVL *T2);
void arvore_avl_uniao(AVL *T1, AVL *T2);
void arvore_avl_intersecao(AVL *T1, AVL *T2, AVL *T3);

#endif
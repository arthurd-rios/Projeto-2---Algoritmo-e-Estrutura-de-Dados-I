#include "avl.h"

typedef struct no_ NO;

struct no_{

    int chave;
    NO *esq;
    NO *dir;
    int fb;

};

struct avl{

    NO *raiz;
    int profunidade;

};

AVL *arvore_avl_criar (){

AVL *t = (AVL *)malloc(sizeof(AVL));

if(t != NULL){

t->raiz = NULL;
t->profunidade = -1;

}

return t;

}

int avl_altura(NO *no){

    if(no == NULL)
        return -1;

    int alturaesq, alturadir;

    alturaesq = avl_altura(no->esq);
    alturadir = avl_altura(no->dir);

    if(alturaesq > alturadir)
        return (1 + alturaesq);

    return (1 + alturadir);

}

NO *rotacao_direita(NO *a){
    
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->fb = avl_altura(a->esq) - avl_altura(a->dir);
    b->fb = avl_altura(b->esq) - avl_altura(b->dir);

    return b;

}

NO *rotacao_esquerda(NO *a){
    
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->fb = avl_altura(a->esq) - avl_altura(a->dir);
    b->fb = avl_altura(b->esq) - avl_altura(b->dir);

    return b;

}

NO *rotacao_direita_esquerda(NO *a){
    
    a->dir = rotacao_direita(a->dir);
    return rotacao_esquerda(a);

}

NO *rotacao_esquerda_direita(NO *a){
    
    a->esq = rotacao_esquerda(a->esq);
    return rotacao_direita(a);

}

NO *avl_inserir_no(NO *raiz, int chave){

    if(raiz == NULL){

        NO *novo = (NO *)malloc(sizeof(NO));

        novo->chave = chave;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->fb = 0;

        raiz = novo;

    }

    else{

        if(raiz->chave > chave)
            raiz->esq = avl_inserir_no(raiz->esq, chave);

        if(raiz->chave < chave)
            raiz->dir = avl_inserir_no(raiz->dir, chave);
    
    }

    raiz->fb = avl_altura(raiz->esq) - avl_altura(raiz->dir);

    if(raiz->fb == -2){

        if(raiz->dir->fb <= 0)
            raiz = rotacao_esquerda(raiz);

        else
            raiz = rotacao_direita_esquerda(raiz);

    }

    if(raiz->fb == 2){

        if(raiz->esq->fb >= 0)
            raiz = rotacao_direita(raiz);

        else 
            raiz = rotacao_esquerda_direita(raiz);

    }

    return raiz;

}

bool arvore_avl_inserir (AVL *T, int chave){

    if(T != NULL)
        T->raiz = avl_inserir_no(T->raiz, chave);

    if(T->raiz != NULL)
        return true;

    return false;

}

void avl_imprimir_no(NO *raiz){

    if(raiz != NULL){

        avl_imprimir_no(raiz->esq);
        printf("%d ", raiz->chave);
        avl_imprimir_no(raiz->dir);

    }

}

void arvore_avl_imprimir (AVL *T){

    if(T != NULL && !(arvore_avl_vazia(T)))
        avl_imprimir_no(T->raiz);

}

void avl_nos_apagar(NO **raiz){

    if ((*raiz) != NULL){

        avl_nos_apagar(&(*raiz)->esq);
        avl_nos_apagar(&(*raiz)->dir);

        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;

        free(*raiz);
        *raiz = NULL;

    }

}

void arvore_avl_apagar (AVL **T){

    if(*T != NULL){

        avl_nos_apagar(&(*T)->raiz);
        
        free(*T);
        *T = NULL;

    }

}

void trocar_maior_esquerda(NO *troca, NO *raiz, NO *anterior){

    if(troca->dir != NULL){
    
        trocar_maior_esquerda(troca->dir, raiz, troca);
        return;

    }

    if(raiz == anterior)
        anterior->esq = troca->esq;

    else
        anterior->dir = troca->esq;

    raiz->chave = troca->chave;

    free(troca);
    troca = NULL;

}

NO *avl_remover(NO **raiz, int chave){

    NO *p;

    if(*raiz == NULL)
        return NULL;

    else if(chave == (*raiz)->chave){

        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){

            p = *raiz;

            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            
            else   
                *raiz = (*raiz)->esq;
            
            free(p);
            p = NULL;

        }

        else
            trocar_maior_esquerda((*raiz)->esq, (*raiz), (*raiz));

    }

    else if(chave < (*raiz)->chave)
        (*raiz)->esq = avl_remover(&(*raiz)->esq, chave);

    else if(chave > (*raiz)->chave)
        (*raiz)->dir = avl_remover(&(*raiz)->dir, chave);

    if(*raiz != NULL){
        (*raiz)->fb = avl_altura((*raiz)->esq) - avl_altura((*raiz)->dir);


    if((*raiz)->fb == -2){

        if((*raiz)->dir->fb <= 0)
            *raiz = rotacao_esquerda(*raiz);

        else
            *raiz = rotacao_direita_esquerda(*raiz);

    }

    if((*raiz)->fb == 2){

        if((*raiz)->esq->fb >= 0)
            *raiz = rotacao_direita(*raiz);

        else 
            *raiz = rotacao_esquerda_direita(*raiz);

    }
    }

    return *raiz;

}

bool arvore_avl_remover(AVL *T, int chave){

    if(T != NULL){

        T->raiz = avl_remover(&T->raiz, chave);

        if(T->raiz != NULL)
            return true;

    }

    return false;

}

NO *avl_buscar_no(NO *raiz, int chave){

    if(raiz == NULL)
        return NULL;

    if(raiz->chave == chave)
        return raiz;
    
    if(raiz->chave > chave)
        return(avl_buscar_no(raiz->esq, chave));

    if(raiz->chave < chave)
        return(avl_buscar_no(raiz->dir, chave));
    
}

bool arvore_avl_busca(AVL *T, int chave){

    if(T != NULL){

        NO *no = avl_buscar_no(T->raiz, chave);

        if(no != NULL)
            return true;

    }

    return false;       // A função retorna falso caso a chave não seja encontrada, ou caso a árvore não exista

}

bool arvore_avl_vazia(AVL *T){

    if(T != NULL){

        if(T->raiz == NULL)
            return true;

            return false;

    }

    return true;       // Caso a árvore não exista, retorna verdadeiro para que nenhuma operação de remoção seja feita, pois será considerada vazia

}

NO *avl_copiar(NO *raiz){

    if(raiz == NULL)
        return NULL;

    NO *no = (NO *)malloc(sizeof(NO));

    if(no == NULL)
        return NULL;

        
    no->chave = raiz->chave;
    no->fb = raiz->fb;
    no->esq = avl_copiar(raiz->esq);
    no->dir = avl_copiar(raiz->dir);

    return no;

}

void arvore_avl_copiar(AVL *T1, AVL *T2){

    if(T1 == NULL || T2 == NULL)
        return;

    T2->raiz = avl_copiar(T1->raiz);

}

void avl_uniao(AVL *T1, NO *raiz){

    if(raiz != NULL){

        if(!arvore_avl_busca(T1, raiz->chave))
            arvore_avl_inserir(T1, raiz->chave);

        avl_uniao(T1, raiz->esq);
        avl_uniao(T1, raiz->dir);

    }

}

void arvore_avl_uniao(AVL *T1, AVL *T2){

    if(T1 == NULL || T2 == NULL)
        return;

    avl_uniao(T1, T2->raiz);

}

void avl_intersecao(AVL *T1, NO *raiz, AVL *T3){

    if(raiz != NULL){

        if(arvore_avl_busca(T1, raiz->chave))
            arvore_avl_inserir(T3, raiz->chave);

        avl_intersecao(T1, raiz->esq, T3);
        avl_intersecao(T1, raiz->dir, T3);

    }

}

void arvore_avl_intersecao(AVL *T1, AVL *T2, AVL *T3){

    if(T1 == NULL || T2 == NULL || T3 == NULL)
        return;

    avl_intersecao(T1, T2->raiz, T3);

}
#include "arn.h"

typedef struct no_ NO;

struct no_{

    int chave;
    NO *esq;
    NO *dir;
    int cor;  // Preto = 0; Vermelho = 1

};

struct arn{

    NO *raiz;
    int profunidade;

};

ARN *arvore_rn_criar(){

    ARN *t = (ARN *)malloc(sizeof(ARN));

    if(t != NULL){

        t->raiz = NULL;
        t->profunidade = -1;

    }

    return t;

}

void inverter_cor(NO *no){

    no->cor = !no->cor;

    if(no->esq != NULL)
        no->esq->cor = !no->esq->cor;

    if(no->dir != NULL)
        no->dir->cor = !no->dir->cor;  

}

NO *rotacao_direita_rn(NO *no){

    NO *aux = no->esq;

    no->esq = aux->dir;
    aux->dir = no;
    aux->cor = no->cor;
    no->cor = 1;

    return aux;

}

NO *rotacao_esquerda_rn(NO *no){

    NO *aux = no->dir;

    no->dir = aux->esq;
    aux->esq = no;
    aux->cor = no->cor;
    no->cor = 1;

    return aux;

}

int vermelho(NO *no){

    if (no == NULL)
        return false;

    return(no->cor);

}

NO *fixup(NO *no){

    if (vermelho(no->dir))
        no = rotacao_esquerda_rn(no);

    if (vermelho(no->esq) && vermelho(no->esq->esq))
        no = rotacao_direita_rn(no);

    if (vermelho(no->esq) && vermelho(no->dir))
        inverter_cor(no);

    return no;

}

NO *arn_inserir_no(NO *raiz, int chave){

    if(raiz == NULL){

        NO *novo = (NO *)malloc(sizeof(NO));
        novo->chave = chave;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->cor = 1;

        raiz = novo;

    }

    else{

        if(raiz->chave > chave)
            raiz->esq = arn_inserir_no(raiz->esq, chave);

        if(raiz->chave < chave)
            raiz->dir = arn_inserir_no(raiz->dir, chave);
    
    }

    if(vermelho(raiz->dir) && !vermelho(raiz->esq))
        raiz = rotacao_esquerda_rn(raiz);

    if(vermelho(raiz->esq) && vermelho(raiz->esq->esq))
        raiz = rotacao_direita_rn(raiz);

    if(vermelho(raiz->esq) && vermelho(raiz->dir))
        inverter_cor(raiz);

    return raiz;

}

bool arvore_rn_inserir (ARN *T, int chave){

    if(T != NULL)
        T->raiz = arn_inserir_no(T->raiz, chave);

    if(T->raiz != NULL)
        return true;

    return false;

}

void arn_imprimir_no(NO *raiz){

    if(raiz != NULL){

        arn_imprimir_no(raiz->esq);
        printf("%d ", raiz->chave);
        arn_imprimir_no(raiz->dir);

    }

}

void arvore_rn_imprimir (ARN *T){

    if(T != NULL && !(arvore_rn_vazia(T)))
        arn_imprimir_no(T->raiz);    

}

void arn_nos_apagar(NO **raiz){

    if ((*raiz) != NULL){

        arn_nos_apagar(&(*raiz)->esq);
        arn_nos_apagar(&(*raiz)->dir);

        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;

        free(*raiz);
        *raiz = NULL;

    }

}

void arvore_rn_apagar(ARN **T){

    if(*T != NULL){

        arn_nos_apagar(&(*T)->raiz);
        
        free(*T);
        *T = NULL;

    }

}

NO *mover_vermelho_esquerda(NO *no){

    if (!vermelho(no->esq) && !vermelho(no->esq->esq)){

        inverter_cor(no);

        if (vermelho(no->dir->esq)){

            no->dir = rotacao_direita_rn(no->dir);
            no = rotacao_esquerda_rn(no);
            inverter_cor(no);

        }
    }

    return no;

}

NO *mover_vermelho_direita(NO *no){

    inverter_cor(no);

    if (vermelho(no->esq->esq)){

        no = rotacao_direita_rn(no);
        inverter_cor(no);

    }
    
    return no;

}

void trocar_menor_direita(NO *troca, NO *raiz, NO *anterior){

    if(troca->esq != NULL){
    
        trocar_menor_direita(troca->esq, raiz, troca);
        return;

    }

    if(raiz == anterior)
        anterior->dir = troca->dir;

    else
        anterior->esq = troca->dir;

    raiz->chave = troca->chave;

    free(troca);
    troca = NULL;

}

NO *arn_remover(NO *raiz, int chave){

    if(raiz == NULL)
        return NULL;

    if (chave < raiz->chave){

        if (raiz->esq != NULL && !vermelho(raiz->esq) && !vermelho(raiz->esq->esq))
            raiz = mover_vermelho_esquerda(raiz);

        raiz->esq = arn_remover(raiz->esq, chave);

    }

    else{

        if (vermelho(raiz->esq))
            raiz = rotacao_direita_rn(raiz);

        if (chave == raiz->chave && raiz->dir == NULL){

            free(raiz);
            return NULL;

        }

        if (raiz->dir != NULL && !vermelho(raiz->dir) && !vermelho(raiz->dir->esq))
            raiz = mover_vermelho_direita(raiz);

        if (chave == raiz->chave){

            NO *menor = raiz->dir;

            while (menor->esq != NULL)
                menor = menor->esq;

            raiz->chave = menor->chave;
            raiz->dir = arn_remover(raiz->dir, menor->chave);

        }
        
        else
            raiz->dir = arn_remover(raiz->dir, chave);

    }

    return fixup(raiz);
}
    




bool arvore_rn_remover(ARN *T, int chave){

    if(T != NULL && T->raiz != NULL){

        T->raiz = arn_remover(T->raiz, chave);

        if(T->raiz != NULL)
            return true;

    }

    return false;    

}

NO *arn_buscar_no(NO *raiz, int chave){

    if(raiz == NULL)
        return NULL;

    if(raiz->chave == chave)
        return raiz;
    
    if(raiz->chave > chave)
        return(arn_buscar_no(raiz->esq, chave));

    if(raiz->chave < chave)
        return(arn_buscar_no(raiz->dir, chave));

}

bool arvore_rn_busca(ARN *T, int chave){

    if(T != NULL){

        NO *no = arn_buscar_no(T->raiz, chave);

        if(no != NULL)
            return true;

    }

    return false;       // A função retorna falso caso a chave não seja encontrada, ou caso a árvore não exista

}

bool arvore_rn_vazia(ARN *T){

    if(T != NULL){

        if(T->raiz == NULL)
            return true;

            return false;

    }

    return true;       // Caso a árvore não exista, retorna verdadeiro para que nenhuma operação de remoção seja feita, pois será considerada vazia

}

NO *arn_copiar(NO *raiz){

    if(raiz == NULL)
        return NULL;

    NO *no = (NO *)malloc(sizeof(NO));

    if(no == NULL)
        return NULL;

        
    no->chave = raiz->chave;
    no->cor = raiz->cor;
    no->esq = arn_copiar(raiz->esq);
    no->dir = arn_copiar(raiz->dir);

    return no;

}

void arvore_rn_copiar(ARN *T1, ARN *T2){

    if(T1 == NULL || T2 == NULL)
        return;

    T2->raiz = arn_copiar(T1->raiz);

}

void arn_uniao(ARN *T1, NO *raiz){

    if(raiz != NULL){

        if(!arvore_rn_busca(T1, raiz->chave))
            arvore_rn_inserir(T1, raiz->chave);

        arn_uniao(T1, raiz->esq);
        arn_uniao(T1, raiz->dir);

    }

}

void arvore_rn_uniao(ARN *T1, ARN *T2){

    if(T1 == NULL || T2 == NULL)
        return;

    arn_uniao(T1, T2->raiz);

    }



void arn_intersecao(ARN *T1, NO *raiz, ARN *T3){

    if(raiz != NULL){

        if(arvore_rn_busca(T1, raiz->chave))
            arvore_rn_inserir(T3, raiz->chave);

        arn_intersecao(T1, raiz->esq, T3);
        arn_intersecao(T1, raiz->dir, T3);

    }

}

void arvore_rn_intersecao(ARN *T1, ARN *T2, ARN *T3){

    if(T1 == NULL || T2 == NULL || T3 == NULL)
        return;

    arn_intersecao(T1, T2->raiz, T3);


}

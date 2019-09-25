#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    int dado;
    int altura;
    struct arvore * esq, * dir, *pai;
} Arv;

void Printa(Arv * tree, int nv) {
    if (tree != NULL) {
        int i = 0;
        Printa(tree -> esq, nv+1);
        while (i < nv) {
            printf("\t");
            i++;
        }
        printf("%d\n", tree->dado);

        Printa(tree->dir, nv+1);
    }
}

int maior (int x, int y) {
    if (x > y) {
        return x;
    }
    else {
        return y;
    }
}

int altura(Arv * no) {
    if (no == NULL) {
        return -1;
    }
    else {
        return no->altura;
    }
}

int fat_balanceamento(Arv * no) {
    return labs(altura(no->esq) - altura(no->dir));
}

void rotacao_RR(Arv** raiz) {
    Arv * no;
    Arv * help = (*raiz) -> pai;

    no = (*raiz)->dir;
    (*raiz)->pai = no;
    (*raiz)->dir = no->esq;
    if (no -> esq != NULL) {
        no -> esq -> pai = (*raiz);
    }
    no -> esq = (*raiz);
    (*raiz)->altura = maior(altura((*raiz)->dir), altura((*raiz)->esq)) + 1;
    no -> altura = maior(altura(no->dir), (*raiz)->altura) + 1;

    if (help != NULL) {
        if (help -> esq == (*raiz)) {
            help -> esq = no;
        }
        else {
            help -> dir = no;
        }
    }
    no -> pai = help;

    (*raiz) = no;
}

void rotacao_LL(Arv** raiz) {
    Arv * no;
    Arv * help = (*raiz) -> pai;

    no = (*raiz) -> esq;
    (*raiz) -> pai = no;
    (*raiz) -> esq = no -> dir;
    if (no -> dir != NULL) {
        no -> dir -> pai = (*raiz);
    }
    no -> dir = (*raiz);
    (*raiz) -> altura = maior(altura((*raiz) -> dir), altura((*raiz) -> esq)) + 1;
    no -> altura = maior(altura(no->esq), (*raiz)->altura) + 1;

    if (help != NULL) {
        if (help -> esq == (*raiz)) {
            help -> esq = no;
        }
        else {
            help -> dir = no;
        }
    }

    no -> pai = help;


    (*raiz) = no;
}

void rotacao_LR(Arv ** raiz) {
    rotacao_RR(&(*raiz) -> esq);
    rotacao_LL(raiz);
}

void rotacao_RL(Arv ** raiz) {
    rotacao_LL(&(*raiz) -> dir);
    rotacao_RR(raiz);
}

int insere(Arv ** raiz, int valor) {
    int aux;
    Arv * help;
    if (*raiz == NULL) {
        Arv * novo = (Arv*) malloc(sizeof(Arv));
        if (novo == NULL) {
            return 0;
        }
        novo -> dado = valor;
        novo -> altura = 0;
        novo -> esq = NULL;
        novo -> dir = NULL;
        novo -> pai = NULL;
        *raiz = novo;
        return 1;
    }

    Arv * atual = *raiz;
    if (valor < atual -> dado) {
        aux = insere(&(atual) -> esq, valor);
        help = atual -> esq;
        help -> pai = atual;
        if (aux == 1) {
            if (fat_balanceamento(atual) >= 2) {
                if (valor < (*raiz) -> esq -> dado) {
                    rotacao_LL(raiz);
                }
                else {
                    rotacao_LR(raiz);
                }
            }
        }
    }
    else {
        if (valor > atual->dado) {
            aux = insere(&(atual) -> dir,valor);
            help = atual -> dir;
            help -> pai = atual;
            if (aux == 1) {
                if (fat_balanceamento(atual) >= 2) {
                    if ((*raiz) -> dir -> dado < valor) {
                        rotacao_RR(raiz);
                    }
                    else {
                        rotacao_RL(raiz);
                    }
                }
            }
        }
        else {
            printf("\nvalor duplicado\n");
            return 0;
        }
    }
    atual -> altura = maior(altura(atual -> esq), altura(atual -> dir)) + 1;
    return aux;
}

Arv * procuraMenor(Arv *raiz){
    Arv * aux_1 = raiz;
    Arv * aux_2 = raiz -> esq;

    while(aux_2 != NULL){
        aux_1 = aux_2;
        aux_2 = aux_2 -> esq;
    }
    return aux_1;
}

int removeArv(Arv **raiz, int valor){
    if((*raiz) == NULL){
        printf("Nao ha no para remover.");
        return 0;
    }
    int res;
    if(valor < (*raiz) -> dado){
        if((res = removeArv(&(*raiz) -> esq, valor)) == 1){
            if(fat_balanceamento(*raiz) >= 2){
                if(altura((*raiz) -> dir -> esq) <= altura((*raiz) -> dir -> dir))
                    rotacao_RR(raiz);
                else
                    rotacao_RL(raiz);
            }
        }
    }
    if(valor > (*raiz) -> dado){
        if((res = removeArv(&(*raiz) -> dir, valor)) == 1){
            if(fat_balanceamento(*raiz) >= 2){
                if(altura((*raiz) -> esq -> dir) <= altura((*raiz) -> esq -> esq))
                    rotacao_LL(raiz);
                else
                    rotacao_LR(raiz);
            }
        }
    }
    if(valor == (*raiz) -> dado){
        if(((*raiz) -> esq == NULL || (*raiz) -> dir == NULL)){
            Arv *aux = (*raiz);
            if((*raiz) -> esq != NULL)
                (*raiz) = (*raiz) -> esq;
            else
                (*raiz) = (*raiz) -> dir;
            free(aux);
        }else{
            Arv *aux = procuraMenor((*raiz) -> dir);
            (*raiz) -> dado = aux -> dado;
            removeArv(&(*raiz) -> dir, (*raiz) -> dado);
            if(fat_balanceamento((*raiz)) >= 2){
                if(altura((*raiz) -> esq -> dir) <= altura((*raiz) -> esq -> esq))
                    rotacao_LL(raiz);
                else
                    rotacao_LR(raiz);
            }
        }
        return 1;
    }
    return res;
}

int main () {
    Arv * tree = NULL;
    int op = 1, valor, x;

    while (op != 0) {
        printf("1 - Insere\n2 - Remover\n0 - Sair\n");
        scanf("%d", &op);
        if (op == 1) {
            printf("Entre com o valor que deseja adicionar: \n");
            scanf("%d", &valor);
            printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
            x = insere(&tree, valor);
            Printa(tree, 0);
            printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
        }
        if (op == 2) {
            printf("Entre com o valor que deseja remover: \n");
            scanf("%d", &valor);
            printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
            x = removeArv(&tree, valor);
            Printa(tree, 0);
            printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
        }
    }
    return 0;
}

/*
Algorito de uma lista duplamente encadeada, onde faz a inserção de novas chaves em ordem
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no * prox;
    struct no * ant;
}No;

No* cria(int ch){
    No* novo = (No*)calloc(1,sizeof(No));
    if(novo != NULL){
        novo ->chave = ch;
    }else{
        printf("Chave nao alocada...\n");
        exit(0);
    }
    return novo;
}

No* insereOrdenado(No* L, No* novo){
    No* aux = L;
    if(L == NULL){
        novo ->ant = NULL;
        novo -> prox = NULL;
        return novo;
    }
    while(aux ->prox != NULL && aux->chave < novo ->chave){
        aux = aux -> prox;
    }
    if(novo -> chave <= aux -> chave){
        if(aux -> ant == NULL){
            novo -> prox = aux;
            aux ->ant = novo;
            novo ->ant = NULL;
            return novo;
        }
        else{
            aux -> ant -> prox = novo;
            novo ->prox = aux;
            novo -> ant = aux -> ant;
            aux -> ant = novo;
            return L;
        }
    }else{
        novo -> ant =aux;
        novo -> prox = aux -> prox;
        aux ->prox = novo;
        return L;
    }
}

void imprime(No* L){
    No* aux = L;
    printf("\n");
    while(aux != NULL){
        printf("%d\t", aux -> chave);
        aux= aux -> prox;
    }
     printf("\n");
}

No* removerDuplicadas(No* L){
    No* aux = L;
    No* aux_2 = L;
    No* apaga = NULL;
    if(L == NULL)return NULL;
    if(L -> prox == NULL)return L;

    while(aux != NULL){
        aux_2 = aux -> prox;
        while(aux_2 !=NULL){
            if(aux_2 -> chave == aux -> chave){
                if(aux_2 -> prox == NULL){
                    apaga = aux_2;
                    aux_2 -> ant -> prox = aux_2 -> prox;
                    aux_2 = aux_2 -> ant;
                    free(apaga);
                    break;
                }
                apaga = aux_2;
                aux_2 -> ant -> prox = aux_2 -> prox;
                aux_2 -> prox -> ant = aux_2 -> ant;
                aux_2 = aux_2 -> ant;
                free(apaga);
            }
            aux_2 = aux_2 -> prox;
        }
        aux = aux-> prox;
    }
    return L;
}

int main(){
    No* L = NULL;
    No * novo = NULL;
    int op, ch;

    while(op != 8){
        printf("1-Insira ordenado.\n2-Imprimi.");
        scanf("%d", &op);
        if(op == 1){
            printf("Entre com a chave que deseja adicionar: ");
            scanf("%d", &ch);
            novo = cria(ch);
            L = insereOrdenado(L, novo);
        }
        if(op == 2){
            imprime(L);
        }
        if(op == 3){
            L = removerDuplicadas(L);
        }
    }
}

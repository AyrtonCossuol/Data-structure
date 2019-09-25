#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no * prox;
}No;

No* cria(int ch){
    No* novo = (No*)malloc(sizeof(No));
    if(novo != NULL){
        novo ->chave = ch;
        novo ->prox = NULL;
    }else{
        printf("Chave nao alocada...\n");
        exit(0);
    }
    return novo;
}

No* inseriInicio(No* L, No* novo){
    novo ->prox = L;
    return novo;
}

No* inseriFim(No* L, No* novo){
    No* aux = L;
    if(L == NULL)return novo;
    while(aux -> prox !=NULL){
        aux = aux -> prox;
    }
    aux ->prox = novo;
    return L;
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

No* multiplicar(No* L){
    No* aux = L;
    if(L == NULL)return L;
    while(aux != NULL){
        aux ->chave = (aux ->chave)*10;
        aux = aux ->prox;
    }
    return L;
}

void* verifcarOrdem(No* L){
    No* aux = L;
    int i=0, k=0;
    while(aux != NULL){
        if(i < aux ->chave){
            i = aux ->chave;
            aux = aux ->prox;
        }else{
            k++;
            break;
        }
    }
    if(k == 0){
        printf("\nSua lista esta ordenada....\n");
    }else{
        printf("\nSua lista NAO esta ordenada...\n");
    }
}

void* numRepeticoes(No* L){
    No* aux = L;
    No* aux_2 = L;
    int i, k=0, j=0;

    while(aux != NULL){
        i = aux ->chave;
        aux_2 = L;
        while(aux_2 != NULL){
            if(i == aux_2 ->chave){
                k++;
            }
            aux_2 = aux_2 ->prox;
        }
        j++;
        aux = aux ->prox;
    }
    if(j == k){
        printf("\nNao ha repeticoes na lista\n");
    }else{
        printf("\nO numero de repeticoes eh de: %d\n", (k-j)/2);
    }
}

No* removerDuplicadas(No* L){
    No* ant = L;
    No* aux = L;
    if(aux == NULL){
        return L;
    }
    No* aux2 = L -> prox;
    if(aux2 == NULL){
        return L;
    }
    while(aux -> prox != NULL){
        while(aux2 != NULL){
            if(aux -> chave == aux2 -> chave){
                ant -> prox = aux2 -> prox;
                aux2 -> prox = NULL;
                free(aux2);
                if(aux -> prox == NULL){
                    break;
                }
                aux2 = ant -> prox;
            }else{
                aux2 = aux2 -> prox;
                ant = ant -> prox;
            }
        }
        if(aux -> prox == NULL){
            break;
        }
        aux = aux -> prox;
        aux2 = aux -> prox;
        ant = aux;
    }
    return L;
}

int main(){
    No* L = NULL;
    No* novo = NULL;
    int op, ch;

    while(op != 8){
        printf("\n1-Inseri no inicio.\n2-Inseri no final.\n3-Imprimi a lista.\n4-Multiplicar todos os numeros por 10.\n5-Imprimir se a lista esta em ordem.\n6-Imprimir as ocorrencias de chaves repetidas\n7-Deletar chave repetida.\n8-SAIR.");
        scanf("%d", &op);
        if(op == 1){
            printf("Entre com a chave que deseja adicionar: ");
            scanf("%d", &ch);
            novo = cria(ch);
            L = inseriInicio(L, novo);
        }
        if(op == 2){
            printf("Entre com a chave que deseja adicionar: ");
            scanf("%d", &ch);
            novo = cria(ch);
            L = inseriFim(L, novo);
        }
        if(op == 3){
            imprime(L);
        }
        if(op == 4){
            L = multiplicar(L);
        }
        if(op == 5){
            verifcarOrdem(L);
        }
        if(op == 6){
            numRepeticoes(L);
        }
        if(op == 7){
            L = removerDuplicadas(L);
        }
    }
}

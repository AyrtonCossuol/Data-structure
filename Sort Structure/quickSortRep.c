#include <stdio.h>
#include <stdlib.h>

int compara_int(void *v, int i, int j){
    int *x = (int*)v;
    if(x[i] > x[j]){
        return -1;
    }
    else if(x[i] == x[j])
        return 0;
    else
        return 1;
}

void troca_int (void *v, int i, int j){
    int *x = (int*)v, aux;
    aux = x[i];
    x[i] = x[j];
    x[j] = aux;
}

void printa_int(void *a, int b){
    int *x = (int*)a, i;
    for(i=0; i<b; i++)
        printf("%d\t", x[i]);
    printf("\n\n");
}

void printar(void *v, int tam, void (*prt)(void*, int)){
        prt(v, tam);
}

int valor_mediano(void * v2, int fim) {
    int i = 0, meio;
    int * v = (int*)v2;
    int vet[3];
    for (i = 0; i < 3; i++) {
        vet[i] = rand() % fim;
    }
    if (v[vet[0]] > v[vet[1]] && v[vet[0]] > v[vet[2]]) {
        if (v[vet[1]] > v[vet[2]])
            meio = vet[1];
        else
            meio = vet[2];
    }
    else if (v[vet[1]] > v[vet[0]] && v[vet[1]] > v[vet[2]]) {
        if (v[vet[0]] > v[vet[2]])
            meio = vet[0];
        else
            meio = vet[2];
    }
    else {
        if (v[vet[0]] > v[vet[1]])
            meio = vet[0];
        else
            meio = vet[1];

    }
    return meio;
}


void quicksort(void * v, int inicio, int fim, int * E, int * D, int (*cmp)(void*, int, int), void (*troca)(void*, int, int)) {
    int i;
    int esq = inicio;
    int dir = fim;
    int pivo = valor_mediano(v, fim);
    i = inicio;

    while (i <= dir) {
        if (cmp(v, i, pivo) == 1) {
            troca_int(v, esq, i);
            esq++,i++;
        }
        else if (cmp(v, i, pivo) == -1) {
            troca_int(v, i, dir);
            dir--;
        }
        else {
            i++;
        }
    }
    *E = esq;
    *D = dir;
}

void particiona(void * v, int inicio, int fim, int (*cmp)(void*, int, int), void (*troca)(void*, int, int)) {
    if (inicio < fim) {
        int esq, dir;
        quicksort(v, inicio, fim, &esq, &dir, cmp, troca);
        particiona(v, inicio, esq-1, cmp, troca);
        particiona(v, dir+1, fim, cmp, troca);
    }
}


int main () {
    int i =0,tam;

    printf("Entre com o tam do vetor: \n");
    scanf("%d", &tam);
    int * v = (int *) malloc(tam*sizeof(int));

    printf("Preencha o vetor: \n");
    i = 0;
    while(i < tam) {
        scanf("%d", &v[i]);
        i++;
    }

    printf("Vetor antes: \n");
    printar(v, tam, &printa_int);

    printf("\n\n");

    particiona(v, 0, tam-1, &compara_int, &troca_int);

    printf("Vetor depois: \n");
    printar(v, tam, &printa_int);

    printf("\n");
    return 0;
}

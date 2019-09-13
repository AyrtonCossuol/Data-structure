#include <stdio.h>
#include <stdlib.h>

void criaHeap(int *vet, int i, int f){// i = INICIo  f = FIM
    int aux = vet[i];
    int j = (i*2)+1;
    while(j <= f){
        if(j < f){
            if(vet[j] < vet[j+1]){
                j = j + 1;
            }
        }
        if(aux < vet[j]){
            vet[i] = vet[j];
            i = j;
            j = (2*i) + 1;
        }else{
            j = f + 1;
        }
    }
    vet[i] = aux;
}

void heapSort(int *vet, int tam){
    int i, aux;
    for(i = (tam-1)/2 ; i >=0 ; i--){
        criaHeap(vet, i, tam-1);
    }
    /*for(i = (tam-1); i > 0 ; i--){
        aux = vet[0];
        vet[0] = vet[i];            CASO QUEIRA ORDENAR O HEAP EM ORDEM CREACENTE.
        vet[i] = aux;
        criaHeap(vet, 0 , i-1);
    }*/
}

int main(){
    int vet[9] = {33,32,28,31,29,26,25,30,27};
    int i;

    printf("Esse é seu HEAP de entrada\n");
    for(i = 0 ; i < 9 ; i++)
        printf("%d\t", vet[i]);

    heapSort(vet,9);

    printf("\nEsse é seu HEAP ordenado\n");
    for(i = 0 ; i < 9 ; i++)
        printf("%d\t", vet[i]);
}

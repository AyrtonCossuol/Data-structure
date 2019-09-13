#include <stdio.h>
#include <stdlib.h>

int separa(int *v, int p, int r){
    int c = v[p], i = p+1, j = r, t;
    while(i <= j){
        if(v[i] <= c){
            v[i-1] = v[i];
            ++i;
        }else{
            t = v[i], v[i] = v[j], v[j] = t;
            --j;
        }
    }
    v[j] = c;
    return j;
}

void quicksort(int *v, int ini, int fim){
    if(ini < fim){
        int pivo = separa(v, ini, fim);
        quicksort(v, ini, pivo-1);
        quicksort(v, pivo+1, fim);
    }
}


int main(){
    int *v;
    int i, tam, num;

    printf("\nEntre com o tamanho do vetor que deseja: ");
    scanf("%d", &tam);

    v = (int*)malloc(tam*sizeof(int));
    if(v == NULL){
        printf("Erro de alocacao.\n");
        exit(0);
    }

    printf("\nEntre com os elementos no vetor: ");
    for(i = 0 ; i < tam; i++){
        printf("\nElemento %d:\t ", i+1);
        scanf("%d", &num);
        v[i] = num;
    }

    printf("\n\nSeu VETOR:::::::::::::::::::::::::::::\n");
    for(i = 0 ; i < tam ; i++){
        printf("%d\t", v[i]);
    }

    quicksort(v, 0, tam);

    printf("\n\nSeu vetor ordenado eh:::::::::::::\n");
    for(i = 1 ; i < tam+1 ; i++){
        printf("%d\t", v[i]);
    }
}

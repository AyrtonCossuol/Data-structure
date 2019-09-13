#include <stdio.h>
#include <stdlib.h>

void merge(int *v, int p, int q, int r){
    int i, j, k;
    int *temp = (int*)malloc((r-p)*sizeof(int));
    i = p; j = q; k = 0;
    while(i < q && j < r){
        if(v[i] <= v[j]){
            temp[k++] = v[i++];
        }else{
            temp[k++] = v[j++];
        }
    }
    while(i < q){
        temp[k++] = v[i++];
    }
    while(j < r){
        temp[k++] = v[j++];
    }
    for(i = p ; i < r ; i++)
	v[i] = temp[i-p];
    free(temp);
}

void mergesort(int *v, int p, int r){
    if(p < r-1){
        int q = (p + r)/2;
        mergesort(v, p, q);
        mergesort(v, q, r);
        merge(v,p,q,r);
    }
}

int main(){
	int *v, tam, i;

	printf("Entre com o tamanho do seu vetor: ");
	scanf("%d", &tam);

	v = (int*)malloc(tam*sizeof(int));

	printf("\nPreencha o vetor\n");
	for(i = 0 ; i < tam ; i++){
		printf("Elemento %d: ", i+1);
		scanf("%d", &v[i]);
	}

	printf("\nSeu vetor nao ordenado eh\n");
	for(i = 0 ; i < tam ; i++){
		printf("%d\t", v[i]);
	}

	mergesort(v, 0, tam+1);
	printf("\nSeu vetor ordenado eh\n");
	for(i = 1 ; i < tam+1 ; i++){
		printf("%d\t", v[i]);
	}
	return 0;
}


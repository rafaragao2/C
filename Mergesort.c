#include<stdio.h>
#include<stdlib.h>
void merge (int *v,int l,int m,int r){
    int i,j,k;
    int *temp=(int*)malloc((r-l)*sizeof(int));
    i=l,j=m,k=0;
    while(i<m&&j<r){
        if(v[i]<=v[j]){
            temp[k]=v[i];i++;k++;
        }
        else{
            temp[k]=v[j];j++;k++;
        }
    }
        while(i<m){
            temp[k]=v[i];i++;k++;
        }
        while(j<r){
            temp[k]=v[j];j++;k++;
        }
        k=0;i=l;
        while(i<r){
            v[i]=temp[k];
            i++;k++;
        }
        free(temp);
    }

void mergeSort(int *vetor, int l, int r){
    if (l < (r-1)){
        int q = (l+r)/2;
        mergeSort(vetor, l, q);
        mergeSort(vetor, q, r);
        merge(vetor, l, q, r);
    }
}

void imprimir_vetor(int vetor[],int qtd){
    int i=0;
    for(i=0;i<qtd;i++){
        printf("%i ",vetor[i]);
    }
    return 0;
}

void main (){
    int vetor[5] = {5,3,7,1,2};
    int *ponteiro = vetor;
    printf("Vetor Original: ");
    imprimir_vetor(vetor,5);
    printf("\n");
    mergeSort(ponteiro,0,5);
    printf("Vetor Final: ");
    imprimir_vetor(vetor,5);
}

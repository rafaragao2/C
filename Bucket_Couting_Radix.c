#include <stdio.h>
#include <stdlib.h>
//Impressão de vetores inteiros
void imprimir_vetor_inteiro(int *vetor,int qtd){
    int i=0;
    for(i=0;i<qtd;i++){
        printf("%i ",vetor[i]);
    }
}

//Impressão de vetores Float
void imprimir_vetor_float(float *vetor,int qtd){
    int i=0;
    for(i=0;i<qtd;i++){
        printf("%.3f ",vetor[i]);
    }
}

//Comparação para encontrar maior numero
int maior(int *v, int tam){
    int i, aux=0;
    for(i=0; i < tam; i++)
        if(v[i] > aux) aux = v[i];
    return aux;
}

//Algoritmo CountingSort:
void countingSort (int *v, int maior,int qtd){
    int max = maior+1;
    int i,aux1[max],aux2[qtd];
    for(i=0;i<=(max);i++) aux1[i]=0;
    for(i=0;i<qtd;i++) aux1[v[i]]++;
    for(i=2;i<=max;i++) aux1[i] = aux1[i]+aux1[i-1];
    for(i=0;i<qtd;i++){
        aux2[aux1[v[i]]-1] = v[i];
        aux1[v[i]] = aux1[v[i]]-1;
    }
    for(i=0;i<qtd;i++) v[i]=aux2[i];
}

//CountingSort usado no radixSORT, com alterações para verificação dígito a digito
void countingSort_radix(int *v, int maior,int qtd){
    int max = 10;
    int i,aux1[max],aux2[qtd];
    for(i=0;i<max;i++) aux1[i]=0;
    for(i=0;i<qtd;i++) aux1[(v[i]/maior)%10]++;
    for(i=1;i<max;i++) aux1[i] = aux1[i]+aux1[i-1];
    for(i=0;i<qtd;i++){
        aux2[aux1[(v[i]/maior)%10]-1] = v[i];
        aux1[(v[i]/maior)%10] = aux1[(v[i]/maior)%10]-1;
    }
    for(i=0;i<qtd;i++) v[i]=aux2[i];
}
//Função mestre do RadixSort
void radixSort(int *v, int tam){
    int i;
    int m = maior(v, tam);
    for(i=1; m/i > 0; i*=10){
        countingSort_radix(v, i, tam);
    }
}

//Função bubbleSort usada no bucketsort
void bubbleSort(float *vetor,int tamanho){
    int aux_1 = 0;
    int i=0;
    int interacoes=0;
    while(interacoes<tamanho){
        for(i=0;i<(tamanho-1);i++){
            if(vetor[i]>vetor[i+1]){
                aux_1 = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux_1;
                i++;
            }
        }
        interacoes++;
    }
}


//Struct balde para BucketSort
typedef struct balde{
  int topo;
  float vetor[5];
}baldee;
//Função mestre do BucketSort
void bucketsort(float *vet, int n){
  baldee balde[9];
  int i, j;
  for(i=0; i <= 9; i++) balde[i].topo = 0;
  for(i=0; i < n;i++){
    int bi = (int)(vet[i]*10)%10;
    balde[bi].vetor[balde[bi].topo] = vet[i];
    (balde[bi].topo)++;
  }
  for(i=0; i < n; i++) bubbleSort(balde[i].vetor, balde[i].topo);
  i= j = 0;
  while(i != n){
    if(balde[j].topo){
      balde[j].topo--;
      vet[i] = balde[j].vetor[balde[j].topo];
      i++;
    }
    else j++;
  }
}

int main (){
    int vetor_inteiro_counting[5] = {7,3,6,9,2};
    int vetor_inteiro_radix[5] = {426,645,876,987,332};
    float vetor_float_bucket[5] = {0.811,0.643,0.412,0.715,0.022};
    int *ponteiro_inteiro_counting = vetor_inteiro_counting;
    int *ponteiro_inteiro_radix = vetor_inteiro_radix;
    int *ponteiro_float_bucket = vetor_float_bucket;
    printf("Vetores Iniciais:\n");
    printf("Vetor Int Couting: ");
    imprimir_vetor_inteiro(ponteiro_inteiro_counting,5);
    printf("\n");
    printf("Vetor Int Radix: ");
    imprimir_vetor_inteiro(ponteiro_inteiro_radix,5);
    printf("\n");
    printf("Vetor Float Bucket: ");
    imprimir_vetor_float(ponteiro_float_bucket,5);
    printf("\n");
    printf("\n");

    printf("Respostas:\n");
    printf("Vetor Int Counting: ");
    countingSort(vetor_inteiro_counting,9,5);
    imprimir_vetor_inteiro(ponteiro_inteiro_counting,5);
    printf("\n");
    printf("Vetor Int Radix: ");
    radixSort(vetor_inteiro_radix,5);
    imprimir_vetor_inteiro(ponteiro_inteiro_radix,5);
    printf("\n");
    printf("Vetor Float Bucket: ");
    bucketsort(ponteiro_float_bucket,5);
    imprimir_vetor_float(ponteiro_float_bucket,5);
    printf("\n");
    return 0;
}

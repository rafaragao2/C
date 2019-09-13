#include <stdio.h>

void imprimir_heap(int vetor[],int qtd){
    int i;
    for(i=1;i<qtd;i++){
        printf("%i ",vetor[i]);
    }
}


void troca (int *v, int a, int b){
	int aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

void subir(int *heap, int pos){
	int j = pos/2;
	if (j>=1){
		if  (heap[j] < heap[pos]){
			troca (heap,j,pos);
			subir(heap,j);
		}
	}
}

void descer(int *heap, int tam, int pos){
	int j = 2*pos;
	if (j <= tam){
		if (j<tam){
			if (heap[j+1] > heap [j]) j = j+1;
		}
		if (heap[pos] < heap [j]){
			troca(heap,pos,j);
			descer(heap, tam, j);
		}
	}
}

void construir_heap(int *v, int tam){
	int i;
	for (i=tam/2;i>=1;i--){
		descer(v, tam, i);
	}
}

void heapSort(int *v, int tam){
	int i, ultimo;
	construir_heap(v,tam);
	for(i=tam;i>0;i--){
		troca(v,1,i);
		ultimo = i-1;
		descer(v,ultimo,1);
	}
}

int main (){
	int heap[7] = {3,7,1,5,8,4,0};
	printf("Vetor: ");
	imprimir_heap(heap,7);
	heapSort(heap,6);
	printf("\n");
	printf("HeapSort: ");
	imprimir_heap(heap,7);
	printf("\n");
	return 0;
}






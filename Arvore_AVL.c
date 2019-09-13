#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	struct no *esq;
	struct no *dir;
	int valor;
	int fb;
}no;

void troca(no *no1, no *no2){
		int aux;
		aux = no1->valor;
		no1->valor = no2->valor;
		no2->valor = aux;
	}

void simplesDireita(no **raiz){
	no *aux = (*raiz)-> esq;
	(*raiz)->esq = aux ->dir;
	aux->dir = (*raiz);
	(*raiz) = aux;
	(*raiz)-> dir -> fb = 0;
	(*raiz)-> fb = ((*raiz)-> dir -> fb) - ((*raiz)-> esq -> fb);
}

void simplesEsquerda(no **raiz){
	no *aux = (*raiz)-> dir;
	(*raiz)-> dir = aux->esq;
	aux->esq = (*raiz);
	(*raiz) = aux;
	(*raiz)-> esq -> fb = 0;
	(*raiz)-> fb = ((*raiz)-> dir -> fb) - ((*raiz)-> esq -> fb);
}

void duplaDireita(no **raiz){
	simplesEsquerda(&((*raiz)->esq));
	simplesDireita(raiz);
}

void duplaEsquerda(no **raiz){
	simplesDireita(&((*raiz)->dir));
	simplesEsquerda(raiz);
}

void inserirNO(no **raiz, int elemento ){
	if(*raiz == NULL){
		no *aux = (no *) malloc(sizeof(no));
		aux->valor = elemento;
		aux->dir = aux->esq = NULL;
		aux->fb = 0;
		*raiz = aux;
	}
	else if(elemento < (*raiz)->valor){
		inserirNO(&(*raiz)-> esq, elemento);
		(*raiz)->fb--;
		if((*raiz)->fb<=(-2)){
			if((*raiz)->esq->fb == (-1))
				simplesDireita(&(*raiz));
			else
				duplaDireita(&(*raiz));
		}
	}
	else if(elemento >= (*raiz)->valor){
		inserirNO(&(*raiz)->dir, elemento);
		(*raiz)->fb++;
		if((*raiz)->fb>=2){
			if((*raiz)->dir->fb == (1))
				simplesEsquerda(&(*raiz));
			else
				duplaEsquerda(&(*raiz));
		}
	}
}

no *DoisFilhos(no *root){
		if(root == NULL) return NULL;
		else if(root->esq == NULL) return root;
		else return DoisFilhos(root->esq);
}

// 0 para encontrado e 1 para não encontrado;
int removerNO(no **raiz, int elemento){
	no *aux = NULL;
	no *filhoMaior = NULL;
	int retorno = 1;
	if(*raiz != NULL){
		if(elemento < (*raiz)->valor){
			retorno = removerNO(&(*raiz)-> esq,elemento);
			if(retorno == 1) return retorno;
			(*raiz)->fb++;
			if((*raiz)->fb >=2){
				if(((*raiz)->dir->fb) == 1)simplesEsquerda(&(*raiz));
				else duplaEsquerda(&(*raiz));
			}
		}
		else if(elemento > (*raiz)-> valor){
			retorno = removerNO(&(*raiz)-> dir,elemento);
			if(retorno == 1) return retorno;
			(*raiz)->fb--; //Fator de balanceamento
			if((*raiz)->fb <= -2 ){
				if(((*raiz)->esq->fb) == -1) simplesDireita(&(*raiz));
				else duplaDireita(&(*raiz));
			}
		}
		else if((*raiz)->esq!=NULL && (*raiz)->dir!=NULL){
			filhoMaior = DoisFilhos((*raiz)->dir);
			troca(*raiz,filhoMaior);
			removerNO(&(*raiz)->dir, elemento);
			(*raiz)->fb--;
		}
		else{
			retorno = 0;
			aux = (*raiz);
			if((*raiz)->esq==NULL) (*raiz) = (*raiz)->dir;
			else *raiz = (*raiz)->esq;
			free(aux);
		}
	}
	else printf("Nao achou");
    return retorno;
}

void imprimeEmOrdem(no *raiz){
	if(raiz!= NULL){
		imprimeEmOrdem((raiz)->esq);
		printf("\nchave: %d fb: %d",raiz->valor, raiz->fb);
		imprimeEmOrdem((raiz)->dir);
	}
}

int main(){
	no *raiz = NULL;
	inserirNO(&raiz,5);
	inserirNO(&raiz,7);
	inserirNO(&raiz,9);
	inserirNO(&raiz,10);
	inserirNO(&raiz,2);
	//removerNO(&raiz,2);
	//removerNO(&raiz,10);
	//removerNO(&raiz,5);
	imprimeEmOrdem(raiz);
	return 0;
}


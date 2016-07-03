#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no NO;
typedef struct arvore_binaria ARVORE_BINARIA;
typedef struct item ITEM;

struct item{
	int frequencia;
	char letra;
};

struct  no{
	ITEM * item;
	NO * noDir;
	NO * noEsq;
};

struct arvore_binaria{
	NO * raiz;
};

ARVORE_BINARIA * criarArvore(){
	ARVORE_BINARIA * arvore = (ARVORE_BINARIA *)malloc(sizeof(ARVORE_BINARIA));
	if(arvore != NULL){
		arvore->raiz = NULL;
	}
	return arvore;
}

NO * criarRaiz(ARVORE_BINARIA * arvore, ITEM *item){
	arvore->raiz = (NO*)malloc(sizeof(NO));
	arvore->raiz->item = item;
	arvore->raiz->noDir = NULL;
	arvore->raiz->noEsq = NULL;

	return arvore->raiz;
}

ITEM * criarItem(int frequencia, char letra){
    ITEM * item = (ITEM*)malloc(sizeof(ITEM));
    item->frequencia = frequencia;
    item->letra = letra;

    return item;
}

NO * inserirFilho(int filho, NO *no, ITEM *item){
	NO *NoFilho = (NO*)malloc(sizeof(NO));

	if(NoFilho != NULL){

		NoFilho->noEsq = NULL;
		NoFilho->noDir = NULL;
		NoFilho->item = item;

		if (filho == FILHO_ESQ){
			no->noEsq = NoFilho;
		}else{
			no->noDir = NoFilho;
		}

		return NoFilho;
	}
}

void inserirFilhos(NO* topo, NO* noE, NO *noD){


	if(topo != NULL){
		topo->noEsq = noE;
		topo->noDir = noD;
	}
}








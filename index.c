#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "arquivo.h"


#define TRUE 1
#define FALSE 0
	

int main(void){
	char nomedoArquivo[10];
	int op, numCaracteres = 0;
	printf("Bem vindo ao compactor com algoritmo de huffman\n");
	printf("Digite a operação desejada:  (1: compactar, 2: descompactar)\n");
	scanf("%d", &op);
	if(op == 1){
		printf("Digite o nome do arquivo\n");
		scanf("%s", nomedoArquivo);
		//printf("\n%s\n", nomedoArquivo);
		char *leitura = ler_arquivo(nomedoArquivo,leitura, &numCaracteres);
		printf("%d\n", numCaracteres);
		compactar(leitura,nomedoArquivo,numCaracteres);
	}else if(op == 2){
		printf("Digite o nome do arquivo\n");
		scanf("%s", nomedoArquivo);
		descompactar(nomedoArquivo);
	}
	
	//descompactar();
	return 0;
}

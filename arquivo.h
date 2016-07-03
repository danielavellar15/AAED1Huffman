#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void escrever_arquivoCompactado(char *nome_arq, char *arvore ,int bits, char *texto, int numeroDeLetras, int numCaracteres){  //Nome do arquivo mais o texto a ser escrito
	int j = 0, i = 0, parada = 0;
	char txt[5] = ".bin";

	strcat(nome_arq, txt);

	FILE *arquivo = fopen(nome_arq, "wb");		//Configura o arquivo para ser escrevível e em Binário "WB"
	if(arquivo == NULL){						//Checa se o arquivo foi lido corretamente
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}

	fwrite(&numCaracteres,sizeof(int),1,arquivo);
	//fwrite(texto,tamanho,1,arquivo);		//Função de escrever no arquivo bin
	while(j != numeroDeLetras){
		if(arvore[i] != NULL){
			j++;
			//fprintf(arquivo, "%ci%d ", arvore[i],i);
			fwrite(&arvore[i],sizeof(char),1,arquivo);
			printf("%c", arvore[i]);
			fwrite("i",sizeof(char),1,arquivo);
			printf("i");
			fwrite(&i,sizeof(int),1,arquivo);
			printf("%d", i);
			fwrite(" ",sizeof(char),1,arquivo);
			printf(" ");
			//printf("%c %d ", arvore[i], i);
		}
			//fprintf(arquivo, "NULL ");
			//printf("null\n");

		i++;
	}



	//fprintf(arquivo, "| %d |", bits);
	fwrite("|",sizeof(char),1,arquivo);
	printf("|");
	fwrite(&bits,sizeof(int),1,arquivo);
	printf("%d", bits);
	fwrite("|",sizeof(char),1,arquivo);
	printf("|");

	if(bits%8 == 0)
		parada = bits/8;
	else
		parada = (bits/8)+1;

	for (i = 0; i < parada; ++i){
		fwrite(&texto[i],sizeof(char),1,arquivo);
		printf("%c", texto[i]);
	}
	//fprintf(arquivo, "%s", texto);
	//printf("%ld\n", sizeof(texto));
	fclose(arquivo);							// fwrite(variavel, tamanho em bytes, tanto de leituras , arquivo)

}

char *ler_arquivo(char *nome_arq, char *palavra, int *nCaracteres){
	char *ch;
	int numCaracteres = 0;
	FILE *arq = fopen(nome_arq, "r");

	if (arq == NULL){
		printf("Não foi possivel abrir o arquivo\n");
	}

	while (!feof(arq)) {
          fread(&ch, 1, 1, arq);
          numCaracteres++;
	}

	printf("%d\n", numCaracteres);
	fseek(arq, SEEK_SET, 0);
	palavra = (char*)malloc(numCaracteres+1*sizeof(char));
	fread(palavra, numCaracteres+1, 1, arq);

	//printf("%s\n", palavra);

	*nCaracteres = numCaracteres;
	//free(palavra);
	//palavra = NULL;
	fclose(arq);

	return palavra;
}

char * ler_arquivoCompactado(char *nome_arq, unsigned char * textoCompactado, int *bits, int *contadorDeLetras, int *numCaracteres){

	char aux;
	char aux2;
	char espaco;
	char *arvoreB = (char*)malloc(5000*sizeof(char));
	int i = 0,j = 0;
	FILE *arq = fopen(nome_arq, "rb");

	if (arq == NULL){
		printf("Não foi possivel abrir o arquivo\n");
	}

	fread(&i,sizeof(int),1,arq);
	*numCaracteres = i;
	//printf("Arvore ----\n");
	while(1){
		//fscanf(arq, "%c%c%d%c", &aux,&aux2,&i,&espaco);
		fread(&aux,sizeof(char),1,arq);
		if(aux == '|'){
			break;
		}
		//printf("%c", aux);
		fread(&aux2,sizeof(char),1,arq);
		//printf("%c ", aux2);
		fread(&i,sizeof(int),1,arq);
		//printf("%d ", i);
		fread(&espaco,sizeof(char),1,arq);	
		//printf("%c \n", espaco);
		
		
		arvoreB[i] = aux;
		*contadorDeLetras = i;
		printf("Arvore[%d] = %c\n",i,arvoreB[i]);
	}
	//fscanf(arq, " %d ", &i);
	fread(&i,sizeof(int),1,arq);
	//printf("%d\n", i);		
	*bits = i;
	//printf("Bits ----- %d\n", *bits);
	//fscanf(arq, "%c", &aux);
	fread(&aux,sizeof(char),1,arq);
	//printf("Texto ------\n");
	i = 0;	
	while(!feof(arq)){
		//fscanf(arq, "%c", &textoCompactado[i]);
		fread(&textoCompactado[i],sizeof(char),1,arq);
		printf("%c", textoCompactado[i]);
		i++;
	}
	//printf("Texto Lido \n");

	i = 0;
    j = 0;
    printf("%c", arvoreB[0]);
    /*printf("%c", arvoreB[0]);

    while(j != contadorDeLetras){
        if(arvoreB[i] != NULL){
            j++;
            printf("%c", arvoreB[i]);
            //fwrite(&i,sizeof(int),1,arquivo);
        }
        i++;
    }*/
	fclose(arq);
	return arvoreB;
}

void escrever_arquivo(char *nome_arq, char *texto){  //Nome do arquivo mais o texto a ser escrito
	int j = 0, i = 0,n=0;

	//printf("Arquivo %s\n", texto);


	/*while(texto[i] != NULL){
		//fwrite(&texto[i],sizeof(char),1,arquivo);
		printf("%c", texto[i]);
		i++;
	}*/

	//printf("-----------------------------------------------------1\n");
	while(nome_arq[i] != NULL){
		i++;
	}
	//printf("%d\n", i);
	for (n = 0; n < 5; n++){
		nome_arq[i] = NULL;
		i--;
	}
	printf("%s\n",nome_arq );

	char txt[4] = " des";

	strcat(nome_arq, txt);
	
	FILE *arq = fopen(nome_arq, "w");		//Configura o arquivo para ser escrevível
	if(arq == NULL){						//Checa se o arquivo foi lido corretamente
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}
	
	fprintf(arq,"%s\n", texto);
	

	//printf("%ld\n", sizeof(texto));
	fclose(arq);							
}

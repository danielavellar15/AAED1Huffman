#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"

#define TRUE 1
#define FALSE 0

typedef struct floresta FLORESTA;
typedef struct mapa_caracters MAPA_CARACTERS;

struct floresta{
    ARVORE_BINARIA * arvoreP;
    FLORESTA * proxArvore;
};

struct mapa_caracters{
    char * caminho;
    char letra;
    MAPA_CARACTERS * prox_letra;
};

MAPA_CARACTERS * percorrerArvoreAux(int lado,MAPA_CARACTERS * mapaAux, NO * no,char * caminhoL, int i,int * altura);
char * ler_arquivoCompactado(char *, unsigned char *, int *, int *, int*);

MAPA_CARACTERS * criarMapaCaracters(){
    MAPA_CARACTERS * mapa_caracters = (MAPA_CARACTERS*)malloc(sizeof(MAPA_CARACTERS));
    if(mapa_caracters != NULL){
        mapa_caracters->caminho = (char*)malloc(sizeof(char));
        mapa_caracters->letra = NULL;
    }

    return mapa_caracters;
}

FLORESTA * criarFloresta(){
    FLORESTA * floresta = (FLORESTA*)malloc(sizeof(FLORESTA));
    if(floresta != NULL){
        floresta->arvoreP = NULL;
        floresta->proxArvore = NULL;
    }

    return floresta;
}

int tamanhoTexto(char * str){
    int i = 0;
    for(;str[i] != 0; ++i);
    return i;
}

void gerarRaizesFreq(FLORESTA * floresta,char * str, int *numerodeNos){
	int i, cont, n = 1;

	FLORESTA * florestaAux = criarFloresta();
	/*ARVORE_BINARIA * arvoreAux = criarArvore();

	NO * noAux = criarNO();
	arvoreAux->raiz = criarNO();*/
   ////printf("-----------criando arvores com as frequencias-----------\n");
	for(i = 0;str[i] != '\0'; ++i){
		////printf("rodou %d vez com a letra %c\n", i+1 ,str[i]);

		if(i == 0){ // primeira caso onde nao ha arvore
		    ////printf("sem letras salvas\n");
            floresta->arvoreP = criarArvore();
            floresta->arvoreP->raiz = criarRaiz(floresta->arvoreP,criarItem(1,str[i]));
            ////printf("letra salva: %c\n",floresta->arvoreP->raiz->item->letra);
            floresta->proxArvore = criarFloresta();
            floresta->proxArvore->arvoreP = criarArvore();
            floresta->proxArvore->arvoreP->raiz = criarRaiz(floresta->proxArvore->arvoreP,criarItem(0,NULL));
		}else{
            florestaAux = floresta;
			for(cont = 0; cont<=i; cont++){
				////printf("rodou \n");
				if(florestaAux->arvoreP->raiz->item->letra == str[i]){
					////printf("achou igual e deu break letra: %c\n", str[i]);
					florestaAux->arvoreP->raiz->item->frequencia++;
					break;

				}else if(florestaAux->arvoreP->raiz->item->letra == NULL){
                        n++;
                        ////printf("nao tem a letra salva vamos adicionar mais uma\n");
						florestaAux->arvoreP->raiz->item->letra = str[i];
						florestaAux->arvoreP->raiz->item->frequencia = 1;
						florestaAux->proxArvore = criarFloresta();
                        florestaAux = florestaAux->proxArvore;
                        florestaAux->arvoreP = criarArvore();
                        florestaAux->arvoreP->raiz= criarRaiz(florestaAux->arvoreP,criarItem(0,NULL));
                        break;

                }else{
                    ////printf("nao e igual a letra %c salva entao vamos pra proxima \n", florestaAux->arvoreP->raiz->item->letra);
                    florestaAux = florestaAux->proxArvore;
                }

			};
		}
	}
    ////printf("-------------terminanda a criacao das arvores------------------\n");
    printf("%d\n", n);
    *numerodeNos = n;
}


ARVORE_BINARIA * pegarMenorFrequencia(FLORESTA * floresta){
    FLORESTA * florestaAux = criarFloresta();
    florestaAux = floresta;
    ARVORE_BINARIA * arvoreMenorFreq = criarArvore();
    arvoreMenorFreq->raiz = criarRaiz(arvoreMenorFreq,criarItem(0,NULL));
    ////printf("pegando arvore de menor frequencia\n");
    for(;florestaAux->arvoreP->raiz->item->frequencia != 0;){
        if(arvoreMenorFreq->raiz->item->frequencia == 0 && florestaAux->arvoreP->raiz->item->frequencia != -1){
            ////printf("entrou no primeiro caso entao a menor frequencia é a primeira posicao que é %i\n", florestaAux->arvoreP->raiz->item->frequencia);

            arvoreMenorFreq = florestaAux->arvoreP;
            florestaAux = florestaAux->proxArvore;
        }else if(arvoreMenorFreq->raiz->item->frequencia > florestaAux->arvoreP->raiz->item->frequencia && florestaAux->arvoreP->raiz->item->frequencia > 0){
            //////printf("entrou no segundo caso\n");
            arvoreMenorFreq = florestaAux->arvoreP;
            florestaAux = florestaAux->proxArvore;
        }else{
            ////printf("letra testada 1 %i\n",florestaAux->arvoreP->raiz->item->frequencia);
            florestaAux = florestaAux->proxArvore;
        }
    }
        //////printf("letra de menor frequencia: %c com %i de frequencia\n",arvoreMenorFreq->raiz->item->letra,arvoreMenorFreq->raiz->item->frequencia);

    return arvoreMenorFreq;
}

ARVORE_BINARIA * pegarSegundaMenorFrequencia(FLORESTA * floresta,ARVORE_BINARIA * arvore){
    FLORESTA * florestaAux = criarFloresta();
    florestaAux = floresta;
    ARVORE_BINARIA * arvoreMenorFreq = criarArvore();
    arvoreMenorFreq->raiz = criarRaiz(arvoreMenorFreq,criarItem(0,NULL));
    //////printf("pegando arvore de segunda menor frequencia\n");
    for(;florestaAux->arvoreP->raiz->item->frequencia != 0;){
        if(arvoreMenorFreq->raiz->item->frequencia == 0 && florestaAux->arvoreP->raiz->item->frequencia > 0 && &florestaAux->arvoreP->raiz->item->letra != &arvore->raiz->item->letra){
            ////printf("entrou no segindo caso entao a menor frequencia é a primeira posicao que é %i\n", florestaAux->arvoreP->raiz->item->frequencia);
            arvoreMenorFreq = florestaAux->arvoreP;
            florestaAux = florestaAux->proxArvore;
        }else if(arvoreMenorFreq->raiz->item->frequencia > florestaAux->arvoreP->raiz->item->frequencia && florestaAux->arvoreP->raiz->item->frequencia > 0){
            //////printf("entrou no segundo caso\n");
            if(florestaAux->arvoreP->raiz->item->letra == arvore->raiz->item->letra){
                florestaAux = florestaAux->proxArvore;
            }else{
                arvoreMenorFreq = florestaAux->arvoreP;
                florestaAux = florestaAux->proxArvore;
            }

        }else{
            ////printf("letra testada 2%i\n",florestaAux->arvoreP->raiz->item->frequencia);
            florestaAux = florestaAux->proxArvore;
        }
    }
        //////printf("letra de segunda menor frequencia: %c com %i de frequencia\n",arvoreMenorFreq->raiz->item->letra,arvoreMenorFreq->raiz->item->frequencia);

    return arvoreMenorFreq;
}

FLORESTA * ultimaArvore(FLORESTA * floresta){
    FLORESTA * florestaAux = criarFloresta();
    florestaAux = floresta;
    while(florestaAux->arvoreP->raiz->item->frequencia != 0){
        florestaAux = florestaAux->proxArvore;
    }
    return florestaAux;
}

FLORESTA * ArvoreCompleta(FLORESTA * floresta){
    FLORESTA * florestaAux = criarFloresta();
    florestaAux = floresta;
    //////printf("FlorestaPrincipal %p, FlorestaAUX %p \n", floresta, florestaAux);
    while(florestaAux->arvoreP->raiz->item->frequencia <= 0){
        florestaAux = florestaAux->proxArvore;
        //////printf("FlorestaPrincipal %p, FlorestaAUX %p \n", floresta, florestaAux);
    }
    return florestaAux;
}

FLORESTA * gerarArvoreFrequencias(FLORESTA * floresta, int *numerodeNos){
    int menor,segundoMenor,n=0;
    ARVORE_BINARIA * menorArvore = criarArvore();
    ARVORE_BINARIA * segundaMenorArvore = criarArvore();
    FLORESTA * ultimaFloresta = criarFloresta();
   ////printf("-------------criando arvore de frequencias agrupadas------------------\n");
    for(;;){
        n++;
        menorArvore = pegarMenorFrequencia(floresta);
        segundaMenorArvore = pegarSegundaMenorFrequencia(floresta,menorArvore);

        //printf("vou juntar a arvore com a menor frequencia de : %i com a segunda menor: %i\n",menorArvore->raiz->item->frequencia,segundaMenorArvore->raiz->item->frequencia);
        if(segundaMenorArvore->raiz->item->frequencia == 0){
            break;
        }
        //////printf("%i\n",segundaMenorArvore->raiz->item->frequencia);
        ultimaFloresta = ultimaArvore(floresta);
        ultimaFloresta->arvoreP->raiz->item->frequencia = (menorArvore->raiz->item->frequencia + segundaMenorArvore->raiz->item->frequencia);
        inserirFilhos(ultimaFloresta->arvoreP->raiz,menorArvore->raiz,segundaMenorArvore->raiz);
        menorArvore->raiz->item->frequencia = -1;
        segundaMenorArvore->raiz->item->frequencia = -1;
        ultimaFloresta->proxArvore = criarFloresta();
        ultimaFloresta->proxArvore->arvoreP = criarArvore();
        ultimaFloresta->proxArvore->arvoreP->raiz = criarRaiz(ultimaFloresta->proxArvore->arvoreP,criarItem(0,NULL));

    }
    printf(" + %d\n", n);
    *numerodeNos += n;
    return floresta;

}

void montarArvore(ARVORE_BINARIA * arvore_binaria,int nLetras,char * arvoreB){
    int  posiV;
    posiV = 1;
    int i = 0;
    ARVORE_BINARIA *arvoreAux = arvore_binaria;



    /*while(i<29){
        if(arvoreB[i] == NULL){
           //printf("null1\n");
            i++;
        }else {
           printf("%c  %d\n", arvoreB[i], i);
            i++;
        }
    }*/

    if(nLetras>2){
        ITEM * item = criarItem(-1, NULL);
        ITEM * itemE = criarItem(-1, arvoreB[2]);
        ITEM * itemD = criarItem(-1, arvoreB[3]);
        arvoreAux->raiz = criarRaiz(arvore_binaria,item);
       //printf("vou comecar a montagem da arvore no vetor %i\n",arvore_binaria->raiz->item->frequencia);
       inserirFilho(0, arvore_binaria->raiz, itemE);
       inserirFilho(1, arvore_binaria->raiz, itemD);

        if(arvoreAux->raiz->noEsq != NULL){
            montarArvoreAux(0,arvoreAux->raiz->noEsq, 1, nLetras,arvoreB);
        }
        if(arvoreAux->raiz->noDir != NULL){
            montarArvoreAux(1, arvoreAux->raiz->noDir, 1, nLetras,arvoreB);
        }
    }


    /*i = 0;

    while(1){
        if(arvoreB[i] == NULL){
               //printf("null\n");
                i++;
        }else if(arvoreB[i] == 'c'){
               //printf("%c %d\n", arvoreB[i], i);
                break;
        }else{
           //printf("%c %d\n", arvoreB[i], i);
            i++;
        }
    }*/




}

void montarArvoreAux(int lado, NO * no, int i, int nLetras, char * arvoreB){
    if(lado == 0){// ir para a esquerda

        i = (i)+(i);

        if(i <= nLetras){
            no->item->letra = arvoreB[i];
            //printf("o no %i tem a letra %c\n",i,no->item->letra);
            ITEM * itemE = criarItem(-1, NULL);
            inserirFilho(0, no, itemE);
            //printf("1");
            if(no->noEsq != NULL){
                montarArvoreAux(0, no->noEsq, i, nLetras, arvoreB);
            }
            ITEM * itemD = criarItem(-1, NULL);
            inserirFilho(1, no, itemD);
            if(no->noDir != NULL){
                montarArvoreAux(1, no->noDir, i, nLetras, arvoreB);
            }
        }
    }else{// ir para a direita


        i = (i+i)+1;


        if(i <= nLetras){
            no->item->letra = arvoreB[i];
            //printf("o no %i tem a letra %c\n",i,no->item->letra);
            ITEM * itemE = criarItem(-1, NULL);
            inserirFilho(0, no, itemE);
            if(no->noEsq != NULL){
                montarArvoreAux(0, no->noEsq, i, nLetras, arvoreB);
            }
            ITEM * itemD = criarItem(-1, NULL);
            inserirFilho(1, no, itemD);
            if(no->noDir != NULL){
                montarArvoreAux(1, no->noDir, i, nLetras, arvoreB);
            }
        }
    }
}

char * recuperaTexto(ARVORE_BINARIA *arvore_binaria, char * textoCompactado,int numBits, int numCaracteres){
    int i;
    int j =7;
    int bitArvore = 1;
    int iTxtComp = 0;
    int iTxtDesComp = 0;
    NO * noAux = arvore_binaria->raiz;
    char * textoDescompactado = (char*)malloc(numCaracteres+1*sizeof(char));
    for(i = 0; i<numBits; i++){
        ////printf("rodou a %i\n", i);
        bitArvore = bitArvore << j;
        bitArvore = textoCompactado[iTxtComp] & bitArvore;
        bitArvore = bitArvore >> j;
        ////printf("rodou2 a %i\n", i);
        if(bitArvore == 0){
            ////printf("achei um zero\n");
            if(noAux->noEsq->item->letra == NULL){
                noAux = noAux->noEsq;
            }else{
                textoDescompactado[iTxtDesComp] = noAux->noEsq->item->letra;
                ////printf("achei a letra: %c\n",textoDescompactado[iTxtDesComp]);
                iTxtDesComp++;
                noAux = arvore_binaria->raiz;
            }
        }else{
        ////printf("achei um\n");
            if(noAux->noDir->item->letra == NULL){
                ////printf("NULL\n");
                noAux = noAux->noDir;
            }else{
                ////printf("else\n");
                textoDescompactado[iTxtDesComp] = noAux->noDir->item->letra;
                ////printf("achei a letra: %c\n",textoDescompactado[iTxtDesComp]);
                iTxtDesComp++;
                noAux = arvore_binaria->raiz;
            }
        }
        bitArvore = 1;
        if(j != 0){
            j--;
        }else{
            j = 7;
            iTxtComp++;
        }
    }
    textoDescompactado[iTxtDesComp] =  '\0';

    return textoDescompactado;

}

void percorrerArvore(ARVORE_BINARIA * arvore, MAPA_CARACTERS * mapa, int * altura){
    int i;
    altura = 0;
   ////printf("altura: %i\n", altura);
    MAPA_CARACTERS * mapaAux = mapa;
    char * caminhoL = (char*)malloc(sizeof(char));
    if(arvore->raiz->noEsq != NULL){
        //////printf("indo a primeira vez pra esquerda\n");
        mapaAux = percorrerArvoreAux(0,mapaAux,arvore->raiz->noEsq,caminhoL,i,altura);
    }
    if(arvore->raiz->noDir != NULL){
        //////printf("indo a primeira vez pra direita\n");
        mapaAux = percorrerArvoreAux(1,mapaAux,arvore->raiz->noDir,caminhoL,i,altura);
        //////printf("terminei a busca\n");
    }


   ////printf("--------------------------ffertfgre\n");
   ////printf("altura: %i\n", altura);
   ////printf("mapa  caminho: %s   letra   %c: \n",mapa->prox_letra->caminho,mapa->prox_letra->letra);
   ////printf("mapaAux  caminho: %s   letra   %c: \n",mapaAux->caminho,mapaAux->letra);

}

MAPA_CARACTERS * percorrerArvoreAux(int lado,MAPA_CARACTERS * mapaAux, NO * no,char * caminhoL, int i,int * altura){
    int count;
   ////printf("altura: %i\n", altura);
    if(lado == 0){// ir para a esquerda
        caminhoL[i] = '0';
        if(no->item->letra == NULL){ // caso nao tenha chegado no no folha
            i++;
            if(no->noEsq != NULL){
                mapaAux = percorrerArvoreAux(0,mapaAux,no->noEsq,caminhoL,i,altura);
            }
            if(no->noDir != NULL){
                mapaAux = percorrerArvoreAux(1,mapaAux,no->noDir,caminhoL,i,altura);
            }

        }else{ // chegou no no folha
            ////printf("caminhi onde vai ser colocado a letra MAPAAUX: %p\n",&caminhoL);
            mapaAux->letra = no->item->letra;
            for (count = 0; count<=i; count++){
                mapaAux->caminho[count] = caminhoL[count];
            }
            mapaAux->caminho[count] = '\0';
            ////printf(" 2   caminhi onde vai ser colocado a letra MAPAAUX: %p\n",&mapaAux->caminho);
            mapaAux->prox_letra = criarMapaCaracters();
            mapaAux = mapaAux->prox_letra;
            return mapaAux;

        }
    }else{// ir para a direita
        caminhoL[i] = '1';
        if(no->item->letra == NULL){ // caso nao tenha chegado no no folha
            i++;
            if(no->noEsq != NULL){
                mapaAux = percorrerArvoreAux(0,mapaAux,no->noEsq,caminhoL,i,altura);
            }
            if(no->noDir != NULL){
                mapaAux = percorrerArvoreAux(1,mapaAux,no->noDir,caminhoL,i,altura);
            }

            }else{ // chegou no no folha
               ////printf("caminhi onde vai ser colocado a letra MAPAAUX: %p\n",&caminhoL);
                mapaAux->letra = no->item->letra;
                for (count = 0; count<=i; count++){
                    mapaAux->caminho[count] = caminhoL[count];
                }
                 mapaAux->caminho[count] = '\0';
                ////printf(" 2   caminhi onde vai ser colocado a letra MAPAAUX: %p\n",&mapaAux->caminho);
                mapaAux->prox_letra = criarMapaCaracters();
                mapaAux = mapaAux->prox_letra;

                return mapaAux;
            }
    }
}

void gerarMapaCaracters(FLORESTA * floresta, MAPA_CARACTERS * mapa, int *alturaArvore){
    /*mapa->caminho = "00";
    mapa->letra = 'b';
    mapa->prox_letra = criarMapaCaracters();
    mapa->prox_letra->caminho = "01";
    mapa->prox_letra->letra = 'c';
    mapa->prox_letra->prox_letra = criarMapaCaracters();
    mapa->prox_letra->prox_letra->caminho = "1";
    mapa->prox_letra->prox_letra->letra = 'a';*/
   ////printf("TESTE ARVORE COMPLETA  \n");
    percorrerArvore(ArvoreCompleta(floresta)->arvoreP,mapa, alturaArvore);
    //printf("letra: %c e caminho: %s\n", mapa->letra, mapa->caminho);
    //printf("letra: %c e caminho: %s\n", mapa->prox_letra->letra, mapa->prox_letra->caminho);
    //printf("letra: %c e caminho: %s\n", mapa->prox_letra->prox_letra->letra, mapa->prox_letra->prox_letra->caminho);
    /*//printf("letra: %c e caminho: %s\n", mapa->prox_letra->prox_letra->prox_letra->letra, mapa->prox_letra->prox_letra->prox_letra->caminho);
    //printf("letra: %c e caminho: %s\n", mapa->prox_letra->prox_letra->prox_letra->prox_letra->letra, mapa->prox_letra->prox_letra->prox_letra->prox_letra->caminho);
    //printf("letra: %c e caminho: %s\n", mapa->prox_letra->prox_letra->prox_letra->prox_letra->prox_letra->letra, mapa->prox_letra->prox_letra->prox_letra->prox_letra->prox_letra->caminho);
    //printf("letra: %c e caminho: %s\n", mapa->prox_letra->prox_letra->prox_letra->prox_letra->prox_letra->prox_letra->letra, mapa->prox_letra->prox_letra->prox_letra->prox_letra->prox_letra->prox_letra->caminho);
    *///////printf("EEEEEEEEEEEEEEEEEEEEe");
    //////printf("\n TESTE   %c\n",mapa->letra);

}

char *montarArvoreVetor(ARVORE_BINARIA * arvore_binaria,int *contadorDeLetras, int numerodeNos){
    int  posiV;
    posiV = 1;
    int i = 0, contador = 0;
    char *arvoreB = (char*)malloc((5000)*sizeof(char));//arvore em vetor
    /*while(i<29){
        if(arvoreB[i] == NULL){
           ////printf("null1\n");
            i++;
        }else {
           ////printf("%c 1  %d\n", arvoreB[i], i);
            i++;
        }
    }*/

   ////printf("vou comecar a montagem da arvore no vetor\n");
    if(arvore_binaria->raiz->noEsq != NULL){
        contador = montarArvoreVetorAux(0, arvoreB, arvore_binaria->raiz->noEsq, posiV, contador);
    }
    if(arvore_binaria->raiz->noDir != NULL){
        contador = montarArvoreVetorAux(1, arvoreB, arvore_binaria->raiz->noDir, posiV, contador);
        ////printf("terminei a montagem\n");
    }

    i = 0;

    //printf("%p \n", arvoreB);
    /*while(1){
        if(arvoreB[i] == NULL){
               //printf("null\n");
                i++;
        }else if(arvoreB[i] == 'c'){
               //printf("%c %d\n", arvoreB[i], i);
                break;
        }else{
           //printf("%c %d\n", arvoreB[i], i);
            i++;
        }
    }*/

    *contadorDeLetras = contador;
    //printf("contador de letras %d\n", contadorDeLetras);


    return arvoreB;

}

int montarArvoreVetorAux(int lado,char * arvoreB, NO * no, int i, int contador){
    if(lado == 0){// ir para a esquerda

       ////printf("%d ----", i);
        ////printf("arvore %c na posição %d\n", arvoreB[i],i);
        i = (i)+(i);
       ////printf("%d \n",i);
        if(no->item->letra == NULL){// caso nao tenha chegado no no folha
            if(no->noEsq != NULL){
                contador = montarArvoreVetorAux(0,arvoreB,no->noEsq,i, contador);
            }
            if(no->noDir != NULL){
                contador = montarArvoreVetorAux(1,arvoreB,no->noDir,i, contador);
            }
        }else{ // chegou no no folha
            ////printf("arvore %s na posição %d\n", arvoreB[i],i);
            arvoreB[i] = no->item->letra;
            contador++;
            ////printf("%c\n", no->item->letra);
            ////printf("arvore %c na posição %d\n", arvoreB[i], i);
        }
    }else{// ir para a direita

       ////printf("%d ----", i);
        i = (i+i)+1;
       ////printf("%d \n",i);

        if(no->item->letra == NULL){// caso nao tenha chegado no no folha

            if(no->noEsq != NULL){
                contador = montarArvoreVetorAux(0,arvoreB,no->noEsq,i, contador);
            }
            if(no->noDir != NULL){
                contador = montarArvoreVetorAux(1,arvoreB,no->noDir,i, contador);
            }
        }else{ // chegou no no folha
            ////printf("arvore %s na posição %d\n", arvoreB[i],i);
            arvoreB[i] = no->item->letra;
            contador++;
            ////printf("%c\n", no->item->letra);
            ////printf("arvore %c na posição %d\n", arvoreB[i], i);
            ////printf("arvore %s na posição %d\n", arvoreB[i],i);
        }
    }
    return contador;
}

MAPA_CARACTERS * retornaLetraMapa(MAPA_CARACTERS * mapa, char letra){
    MAPA_CARACTERS * mapaAux = mapa;


    for(;;){
        if(mapaAux->letra == letra){
            ////printf("mapaAux LETRA: %c CAMINHO: %s\n", mapaAux->letra, mapaAux->caminho);
            ////printf("mapaAux->letra %c\n", mapaAux->letra);
            return mapaAux;
            break;
        }else{
            ////printf("prox_letra\n");
            ////printf("mapaAux LETRA: %c CAMINHO: %s\n", mapaAux->letra, mapaAux->caminho);
            mapaAux = mapaAux->prox_letra;
        }
    }
}

void compactaTexto(MAPA_CARACTERS * mapa, char * str,unsigned char * textoC, int * contC){
    MAPA_CARACTERS * mapaAux;

    int inner,outer;
    int i = 0;
    int contChars = 0;
    int aux = 1;
    //////printf("rodou na letra %s \n",mapa->prox_letra->letra);
   ////printf("Lendo Arvore e preenchendo unsigned Char\n");
    ////printf("retornaLetraMapa %c\n", str[0]);
    mapaAux = retornaLetraMapa(mapa,str[0]);
    ////printf("letra %c\n", mapaAux->letra);

    for(outer = 0; str[outer] !=  '\0';){
    textoC[contChars] = NULL;
        for(inner = 7; inner >= 0; inner--){
            *contC = *contC + 1;
            ////printf("Contc: %i\n",*contC);
            //printf("letra no mapa %c \n", mapaAux->letra);

            ////printf("inner fora == %i\n",inner);
            ////printf("camhinho testado == %s\n",mapaAux->caminho);
            if(mapaAux->caminho[i] == '1'){
               //////printf("1");
                ////printf("inner dentro == %i\n",inner);
                aux = aux << inner;
                //printf("1 cont = %i e o char esta assim: %i \n", inner, textoC[contChars]);
                textoC[contChars] = textoC[contChars] | aux;
                //printf("11 cont = %i e o char esta assim: %i \n", inner, textoC[contChars]);
                aux = 1;
            }else{
               aux = aux << inner;
               //printf("0 cont = %i e o char esta assim: %i \n", inner, textoC[contChars]);
               //textoC[contChars] = textoC[contChars] & aux;
               //printf("00 cont = %i e o char esta assim: %i \n", inner, textoC[contChars]);
               aux = 1;

            }
            if(mapaAux->caminho[i+1] == '\0'){
            //printf("fim do caminho vou para outra letra\n");
                if(str[outer+1] == '\0'){
                //printf("acabou as letras\n");
                    outer++;
                    break;
                }else{
                    i = 0;
                    outer++;
                   //////printf("\nretornaLetraMapa %c\n", str[outer]);
                    mapaAux = retornaLetraMapa(mapa,str[outer]);
                    ////printf("letra %c\n", mapaAux->letra);

                  // //printf("primeira letra no mapa %c \n", mapaAux->letra);
                    //////printf("primeira caminho no mapa %s \n", mapaAux->caminho);
                }
            }else{
                i++;
            }
        }
        //printf("char compactado %i \n",textoC[contChars]);
        contChars++;
    }
}

void compactar(char * str,char*nomeDoArquivo, int numCaracteres){
    int alturaArvore = 0;
    FLORESTA * floresta = criarFloresta();
    MAPA_CARACTERS * mapa = criarMapaCaracters();
    char * arvoreB;//arvore em vetor
    unsigned char * textoCompactado = (unsigned char*)malloc(1024*sizeof(char));
    int contChar = 0, j=0, i=0;//numero de bits para ler
    int contadorDeLetras = 0, numerodeNos;





    //printf("\nvou chamar gerarRaizesFreq\n\n");
    gerarRaizesFreq(floresta, str, &numerodeNos);
    //printf("\nvou chamar gerarMapaCaracters\n\n");
    gerarMapaCaracters(gerarArvoreFrequencias(floresta, &numerodeNos),mapa, &alturaArvore);
    printf("Numero de nos alocados%d\n", numerodeNos*numerodeNos);
    //printf("\nvou chamar montarArvoreVetor\n\n");
    arvoreB = montarArvoreVetor(ArvoreCompleta(floresta)->arvoreP, &contadorDeLetras, numerodeNos);
    //printf("\nvou chamar compactaTexto\n\n");
    compactaTexto(mapa,str,textoCompactado,&contChar);

    //printf("%d\n", contadorDeLetras);

    //printf("%s\n",textoCompactado);

    /*while(1){
        if(arvoreB[i] == NULL){
               //printf("null\n");
                i++;
        }else if(arvoreB[i] == 'c'){
               //printf("%c %d\n", arvoreB[i], i);
                break;
        }else{
           //printf("%c %d\n", arvoreB[i], i);
            i++;
        }
    }*/

    ////printf("primeira char compactado: %i\n",contChar);

    escrever_arquivoCompactado(nomeDoArquivo,arvoreB,contChar,textoCompactado,contadorDeLetras,numCaracteres);

    ////printf("a %c\n",arvoreB[4]);

  /*  while(arvoreB[j] != '\0'){
       ////printf("%c", arvoreB[j]);
        j++;
    }*/
   ////printf("%s\n", textoCompactado);

}

void descompactar(char *nomeDoArquivo){
    char * textoDescompactado;
    ARVORE_BINARIA * arvore_binaria = criarArvore();
    char *arvoreB;
    unsigned char * textoCompactado = (unsigned char*)malloc(2500*sizeof(char));
    int contadorDeLetras, bits, numCaracteres;
    printf("Ler Arquivo Compactado\n");
    arvoreB = ler_arquivoCompactado(nomeDoArquivo, textoCompactado, &bits, &contadorDeLetras,&numCaracteres);
    printf("\nMontando Árvore\n");
    montarArvore(arvore_binaria,contadorDeLetras,arvoreB);
    printf("\nDescompactando texto numCaracteres %d\n", numCaracteres);
    textoDescompactado = recuperaTexto(arvore_binaria,textoCompactado,bits, numCaracteres);
    printf("%s\n",textoDescompactado);
    printf("Escrevendo Arquivo Descompactado\n");
    escrever_arquivo(nomeDoArquivo,textoDescompactado);

    //free(textoCompactado);
    //free(textoDescompactado);
}

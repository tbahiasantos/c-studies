#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITO 9999

char Cidades[100][20], CidadeOrigem[20], CidadeDestino[20];
int **MatrizAdj, qCidades = 0, qEstradas;

void InsereCidade(char Cidade[]) {

	int i, ExisteCidade = 0;

	for (i=0; i<qCidades; i++) {
		if (!strcmp(Cidades[i], Cidade))
			ExisteCidade = 1;
	}

	if (!ExisteCidade) {
		strcpy(Cidades[qCidades], Cidade);
		qCidades++;
	}

}

int RetornaIndice(char Cidade[]) {

	int i;

	for (i=0; i<qCidades; i++)
		if (!strcmp(Cidades[i], Cidade))
			return i;

	return -1;
}

int** AlocaMatriz(int Lin, int Col) {

	int i, j;

	int **Matriz = (int**) malloc(Lin * sizeof(int*));
	
	for (i=0; i<Lin; i++) { 
		Matriz[i] = (int*) malloc(Col * sizeof(int)); 
    	for (j=0; j<Col; j++){ 							
        	Matriz[i][j] = 0; 						
       	}
  	}

	return Matriz; 											
}

void CarregaMatriz(char NomeArquivo[]) {

	FILE *ptr_arq;
	char CidadeX[20], CidadeY[20];
	int i, Distancia, Lin, Col;

	ptr_arq = fopen(NomeArquivo, "r");

	if (!ptr_arq) {
	      printf("Erro na abertura do arquivo!\n");   
	      exit(1);
	}
	
	else {

		fscanf (ptr_arq, "%d", &qEstradas);						

		i = 0;
		while (i < qEstradas) {
			fscanf (ptr_arq, "%s %s %d", CidadeX, CidadeY, &Distancia);
			InsereCidade(CidadeX);
			InsereCidade(CidadeY);
			i++;							
		}
					
	}

	fclose(ptr_arq);

	ptr_arq = fopen(NomeArquivo, "r");

	if (!ptr_arq) {
	      printf("Erro na abertura do arquivo!\n");   
	      exit(1);
	}
	
	else {

		MatrizAdj = AlocaMatriz(qCidades, qCidades);

		fscanf (ptr_arq, "%d", &qEstradas);

		i = 0;
		while(i < qEstradas) {
			fscanf (ptr_arq, "%s %s %d", CidadeX, CidadeY, &Distancia);
			Lin = RetornaIndice(CidadeX);
			Col = RetornaIndice(CidadeY);
			MatrizAdj[Lin][Col] = Distancia;
			MatrizAdj[Col][Lin] = Distancia;
			i++;
		}

		fscanf(ptr_arq, "%s %s", CidadeOrigem, CidadeDestino);

	}		

	fclose(ptr_arq);

}

//Algoritmo inspirado pelo artigo 'Dijkstra's Algorithm in C', do site 'The Crazy Programmer'
//https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
void Dijkstra() {
 
	int **Grafo, Distancia[qCidades], Predecessor[qCidades], Visitado[qCidades], Caminho[qCidades], IndiceOrigem, IndiceDestino;
	int Cont, MenorDistancia, ProxVertice, i, j;

	Grafo = AlocaMatriz(qCidades, qCidades);
	IndiceOrigem = RetornaIndice(CidadeOrigem);
	IndiceDestino = RetornaIndice(CidadeDestino);
	
	//Predecessor[] registra o predecessor de cada vertice
	//Cont guarda o numero de vertices vistos ate entao
	//Cria o Grafo
	for(i=0; i<qCidades; i++)
		for(j=0; j<qCidades; j++)
			if(MatrizAdj[i][j] == 0)
				Grafo[i][j] = INFINITO;
			else
				Grafo[i][j] = MatrizAdj[i][j];
	
	//Inicializa Predecessor[], Distancia[] e Visitado[]
	for(i=0; i<qCidades; i++) {
		Distancia[i] = Grafo[IndiceOrigem][i];
		Predecessor[i] = IndiceOrigem;
		Visitado[i] = 0;
	}
	
	Distancia[IndiceOrigem] = 0;
	Visitado[IndiceOrigem] = 1;
	Cont = 1;
	
	while(Cont < qCidades-1) {
		MenorDistancia = INFINITO;
		
		//ProxVertice da o vertice com a menor distancia
		for(i=0; i<qCidades; i++)
			if(Distancia[i] < MenorDistancia && !Visitado[i]) {
				MenorDistancia = Distancia[i];
				ProxVertice = i;
			}
			
			//Checa se ha um caminho melhor por meio do ProxVertice				
			Visitado[ProxVertice] = 1;
			for(i=0; i<qCidades; i++)
				if(!Visitado[i])
					if( (MenorDistancia + Grafo[ProxVertice][i]) < Distancia[i]) {
						Distancia[i] = MenorDistancia + Grafo[ProxVertice][i];
						Predecessor[i] = ProxVertice;
					}
		Cont++;
	}

	i = 0;
	Caminho[i] = IndiceDestino;
	j = IndiceDestino;
	do {
		j = Predecessor[j];
		i++;
		Caminho[i] = j;
	} while(j != IndiceOrigem);
	printf("Menor percurso: ");	
	for (j=i; j>=0; j--)
		printf("%s ", Cidades[Caminho[j]]);

	printf("\nDistancia total: %d Km\n", Distancia[IndiceDestino]);

}

int main() {

	char NomeArquivo[20];

	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", NomeArquivo);

	CarregaMatriz(NomeArquivo);

	Dijkstra();	

	return 0;
}
/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Fulvio Taroni Monteforte
       Thiago Lima Bahia Santos
Matricula: 20183005944
           20183000302
Descricao do programa: Problema da Mochila | Algoritmo de Forca Bruta + gettimeofday()
Data: 24/09/19
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define MAX_TAM 100

typedef struct {
	int peso;
	int valor;
} Item;

void gerar_arquivo();
void carregar_arquivo(int *cap_mochila, int *num_item, Item mochila[]);
void imprimir_arquivo(int num_item, Item mochila[], int melhor_mochila[]);
void mochila_forcabruta(int cap_mochila, int num_item, Item mochila[], int melhor_mochila[]);

/* Teste da medicao do tempo*/
int main(int argc, char *argv[])
{
	// Variaveis relacionadas com a medicao do tempo:
	
	struct timeval inicio, fim;
	/*estrutura que armazena o tempo total que o programa gasta, relaciona-se com
	a funcao gettimeofday()*/
	
	long totalmicroseg, totalseg;		//tempo total do programa
	
	/* armazenam a diferenca entre o tempo inicial e o final, ou seja, o tempo
	total gasto pelo programa todo. */
	
	//obtendo o tempo em que o programa comeca.
	gettimeofday(&inicio, NULL);
	
	//coloque aqui o algoritmo

	int i, cap_mochila, num_item, melhor_mochila[MAX_TAM];
	Item mochila[MAX_TAM];

	//Função gerar_arquivo() suprimida do código. Utilizar, se necessário.
	//gerar_arquivo();
	carregar_arquivo(&cap_mochila, &num_item, mochila);	
	mochila_forcabruta(cap_mochila, num_item, mochila, melhor_mochila);
	imprimir_arquivo(num_item, mochila, melhor_mochila);
	
	gettimeofday(&fim, NULL);						//obtem tempo final do programa
	totalseg = fim.tv_sec - inicio.tv_sec;			//diferenca em segundos
	totalmicroseg = fim.tv_usec - inicio.tv_usec; 	//diferenca em microsegundos
	
	/*se a diferenca em microssegundos for negativa, os segundos terao que
	emprestar uma unidade; 1 microseg = 10E-6 s. */
	if (totalmicroseg <0)
	{ totalmicroseg += 1000000;
	 totalseg -= 1;
	};

	printf ("\n");
	printf ("***************************************************************\n");
	printf ("Tempo total: %ld segundos e %ld microssegundos.\n", totalseg, totalmicroseg);
	printf ("***************************************************************\n");
	printf ("\n");

	return(0);
}

void gerar_arquivo() {

	FILE *ptr_arq;
	int i, num_item, cap_mochila, sum_peso;
	Item rand_mochila[MAX_TAM];

	printf("Numero de itens : ");
	scanf("%d", &num_item);

	sum_peso = 0;
	for (i=0; i<num_item; i++) {	
		rand_mochila[i].peso = ( rand() % 9 ) + 1;
		sum_peso = sum_peso + rand_mochila[i].peso;
	}

	for (i=0; i<num_item; i++)		
		rand_mochila[i].valor = ( rand() % 9 ) + 1;

	cap_mochila = ( rand() % (sum_peso / 2) ) + 1;

	ptr_arq = fopen("arquivo_leitura.txt","w");	

	if (!ptr_arq) {
	      printf("Erro na abertura do arquivo!\n");   
	      exit(1);
	}
	
	else {

		fprintf (ptr_arq, "%d\n", cap_mochila);
		fprintf(ptr_arq, "%d\n", num_item);

		for(i=0; i<num_item; i++)
			fprintf (ptr_arq, "%d %d\n", rand_mochila[i].peso, rand_mochila[i].valor);
				
	}

	fclose(ptr_arq);	

}

void carregar_arquivo(int *cap_mochila, int *num_item, Item mochila[]) {

	FILE *ptr_arq;
	int i;

	ptr_arq = fopen("arquivo_leitura_35.txt","r");

	if (!ptr_arq) {
	      printf("Erro na abertura do arquivo!\n");   
	      exit(1);
	}
	
	else {

		fscanf (ptr_arq, "%d", cap_mochila);		
		fscanf (ptr_arq, "%d", num_item);				

		i = 0;
		while (!feof(ptr_arq)) {
			fscanf (ptr_arq, "%d %d", &mochila[i].peso, &mochila[i].valor);
			i++;				
		}
	}

	fclose(ptr_arq);

}

void imprimir_arquivo(int num_item, Item mochila[], int melhor_mochila[]) {

	FILE *ptr_arq;
	int i, sum_peso, sum_valor;

	ptr_arq = fopen("arquivo_escrita_35.txt","w");

	if (!ptr_arq) {
	      printf("Erro na abertura do arquivo!\n");   
	      exit(1);
	}

	else {		

		sum_peso = 0;
		sum_valor = 0;

		for (i=0; i<num_item; i++)
			if (melhor_mochila[i] == 1) {
				fprintf (ptr_arq, "%d %d %d\n", i, mochila[i].peso, mochila[i].valor);
				sum_peso = sum_peso + mochila[i].peso;
				sum_valor = sum_valor + mochila[i].valor;
			}

		fprintf (ptr_arq, "%d %d\n", sum_peso, sum_valor);			
		
	}

	fclose(ptr_arq);		

}

void mochila_forcabruta(int cap_mochila, int num_item, Item mochila[], int melhor_mochila[]) {

	int j, k, temp_mochila[MAX_TAM];
	unsigned long long int i, iter;
	Item temp_item, melhor_item;

	iter = pow(2, num_item);

	for (i=0; i<num_item; i++)
		temp_mochila[i] = 0;

	for (i=0; i<iter; i++) {

		j = num_item-1;
		temp_item.peso = 0;
		temp_item.valor = 0;
		
		while (temp_mochila[j] != 0 && j >= 0) {
			temp_mochila[j] = 0;
			j--;
		}			

		temp_mochila[j] = 1;
		
		for (k=0; k<num_item; k++) {

			if (temp_mochila[k] == 1) {
				temp_item.peso = temp_item.peso + mochila[k].peso;
				temp_item.valor = temp_item.valor + mochila[k].valor;
			}

		}

		if (temp_item.valor > melhor_item.valor && temp_item.peso <= cap_mochila) {

			melhor_item.peso = temp_item.peso;
			melhor_item.valor = temp_item.valor;
			
			for (k=0; k<num_item; k++)
				melhor_mochila[k] = temp_mochila[k];

		}

	}

}

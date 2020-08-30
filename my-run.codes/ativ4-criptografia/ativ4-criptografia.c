#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void abrir_arquivo(char nome_arq[], char msg[]);
void permutar_cifra(char msg[]);
void refletir_cifra(char msg[]);
void decodificar_cifra(char msg[]);
void decodificar_simbolo(char msg[]);

int main(){

	char nome_arq[100], msg[10000];

	printf("Digite o nome do arquivo: ");
	scanf("%s", nome_arq);	
	printf("\n");

	abrir_arquivo(nome_arq, msg);
	
	printf("--------------------\n");
	printf("Mensagem codificada:\n");
	printf("--------------------\n");
	printf("%s\n\n", msg);

	permutar_cifra(msg);
	refletir_cifra(msg);
	decodificar_cifra(msg);
	decodificar_simbolo(msg);

	printf("----------------------\n");
	printf("Mensagem decodificada:\n");
	printf("----------------------\n");
	printf("%s\n", msg);

	return 0;

}

void abrir_arquivo(char nome_arq[], char msg[]){

	FILE *ptr_arq;
	int i;
	char c;

	ptr_arq = fopen(nome_arq,"r");

	if (!ptr_arq) {
	      printf("Erro na abertura do arquivo.\n");   
	      exit(1);
	}
	
	else {
		i = 0;
		c = getc(ptr_arq);
		while (!feof(ptr_arq)) {
			msg[i] = c;
			c = getc(ptr_arq);		
			i++;
		}
		i--;
		msg[i] = '\0';
	}

	fclose(ptr_arq);	

}

void permutar_cifra(char msg[]){
	
	int i, j, len;
	char aux;

	len = strlen(msg);

	for(i=0, j=(len-1)-1; i<(len-1)/2; i+=4, j-=4){
		aux = msg[i]; 
		msg[i] = msg[j];	
		msg[j] = aux;
	}
	for(i=1, j=(len-1); i<(len-1)/2; i+=4, j-=4){
		aux = msg[i]; 
		msg[i] = msg[j];	
		msg[j] = aux;
	}

}

void refletir_cifra(char msg[]){
	
	int i, j, len;
	char aux;

	len = strlen(msg);

	for (i=0, j=1; i<len-1; i+=2, j+=2){
		aux = msg[i];
		msg[i] = msg[j];
		msg[j] = aux;
	}

}

void decodificar_cifra(char msg[]){
	
	int i, len;

	len = strlen(msg);

	for (i=0; i<len; i++)
		if (msg[i] != '#'){		
			if (msg[i] == 'A' || msg[i] == 'a' || msg[i] == 'B' ||
				msg[i] == 'B'|| msg[i] == 'C'|| msg[i] == 'c' )
				msg[i] += 23;
			else
				msg[i] -= 3;
		}
	
}

void decodificar_simbolo(char msg[]){

	int i, len;

	len = strlen(msg);

	for (i=0; i<len; i++)
		if (msg[i] == '#')
			msg[i] = ' ';
	
}
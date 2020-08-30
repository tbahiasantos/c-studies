#include<stdio.h>

int Digitos(int N);

int main(){
	int num, resultado;
	printf("Digite um numero inteiro: ");	
	scanf("%d", &num);
	resultado = Digitos(num);
	printf("Resultado: %d\n", resultado);
	return 0;
}

int Digitos(int N){
	int cont = 1;

	if (N < 10)
		return 1;
 	else
		cont = cont + ( Digitos(N/10) );
	
	return cont;
}

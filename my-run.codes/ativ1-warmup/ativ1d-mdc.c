#include<stdio.h>

int mdc(int a, int b);

int main(){
	int num1, num2, resultado;
	printf("Digite dois numeros inteiros: ");	
	scanf("%d %d", &num1, &num2);
	resultado = mdc(num1, num2);
	printf("Resultado: %d\n", resultado);
	return 0;
}

int mdc(int a, int b){

	if (a % b == 0)
		return b;
 	else
		return mdc(b, a%b);
	
}

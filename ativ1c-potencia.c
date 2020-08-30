#include<stdio.h>

int mult(int base, int exp);

int main(){
	int base, exp, result;
	printf("Digite a base e o expoente inteiros: ");
	scanf("%d %d", &base, &exp);
	result = mult(base, exp);
	printf("Resultado: %d\n", result);
	return 0;
}

int mult(int base, int exp){
	if(exp == 0)
		return 1;
	else
		return base * mult(base, exp-1);
}

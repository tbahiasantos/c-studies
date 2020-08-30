#include<stdio.h>

void dec2bin(int dec);

int main(){
	int num;
	printf("Digite um numero inteiro: ");
	scanf("%d", &num);
	printf("Resultado: ");
	dec2bin(num);
	printf("\n");
	return 0;
}

void dec2bin(int dec){

	if (dec/2 == 0)
		printf("%d", dec%2);
 	else{
		dec2bin(dec/2);
		printf("%d", dec%2);
	}
}

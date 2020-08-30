#include<stdio.h>

#define MAX 35660

unsigned long int fatorial_recursivo(int num);
void fatorial_grandesnumeros(int num, int *ptr_vet, int *ptr_tam_vet);
int multiplicar(int num, int *ptr_vet, int tam_vet);

int main(){
	int num;
	printf("Digite um numero inteiro: ");
	scanf("%d", &num);
	if (num <= 20)
		printf("Resultado: %ld\n", fatorial_recursivo(num));
	else{
		int vet[MAX], tam_vet, *ptr_vet, *ptr_tam_vet;
		ptr_vet = vet;
		ptr_tam_vet = &tam_vet;
		fatorial_grandesnumeros(num, ptr_vet, ptr_tam_vet);
	}
	return 0;
}

unsigned long int fatorial_recursivo(int num){
	if (num == 1 || num == 0)
		return 1;
	else
		return num * fatorial_recursivo(num-1);
}

void fatorial_grandesnumeros(int num, int *ptr_vet, int *ptr_tam_vet){
	int fat, pos;
	*ptr_vet = 1;
	*ptr_tam_vet = 1;
	fat = num; 
	while (fat>=1){
		*ptr_tam_vet = multiplicar(fat, ptr_vet, *ptr_tam_vet);
		fat--;
	}
	printf("Resultado: ");
	for (pos=*ptr_tam_vet-1; pos>=0; pos--){
		printf("%d", *(ptr_vet+pos));	
	}
	printf("\n");
}

int multiplicar(int num, int *ptr_vet, int tam_vet){
	int prod, pos, carry;
	pos = 0;
	carry = 0;
	while (pos<tam_vet){
		prod = (num * *(ptr_vet+pos))+carry;
		*(ptr_vet+pos) = prod%10;
		carry = prod/10;		
		pos++;
	}
	while (carry!=0){
		*(ptr_vet+pos) = carry%10;
		carry = carry/10;
		pos++;		
	}
	tam_vet = pos;
	return tam_vet;
}

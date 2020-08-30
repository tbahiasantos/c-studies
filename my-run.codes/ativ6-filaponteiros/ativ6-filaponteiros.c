#include <stdlib.h>
#include <stdio.h>

typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
  TipoChave Chave;
} TipoItem;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
} 

int Vazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras); } 

void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Tras->Prox;
  Fila->Tras->Item = x;
  Fila->Tras->Prox = NULL;
} 

void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
  q = Fila->Frente;
  Fila->Frente = Fila->Frente->Prox;
  *Item = Fila->Frente->Item;
  free(q);
} 

void Imprime(TipoFila Fila)
{ TipoApontador Aux;
  Aux = Fila.Frente->Prox;
  while (Aux != NULL) 
    { printf("%d\n", Aux->Item.Chave);
      Aux = Aux->Prox;
    }
}

void LerArquivo(char NomeArquivo[], TipoFila *Fila){

  FILE *ptr_arq;
  char Solicitacao;
  TipoItem Processo;

  ptr_arq = fopen(NomeArquivo,"r");

  if (!ptr_arq) {
        printf("Erro na abertura do arquivo.\n");   
        exit(1);
  }
  
  else {
      while (!feof(ptr_arq)) {
        
          fscanf(ptr_arq, "%c %d", &Solicitacao, &Processo.Chave);

          if (Solicitacao == 'a')
              Enfileira(Processo, Fila);

          else if (Solicitacao == 'b')
              Desenfileira(Fila, &Processo);
              
          else if (Solicitacao == 'c'){
              printf("\nProcessos na fila:\n");
              Imprime(*Fila);               
          }
              
      }

  }

  fclose(ptr_arq);  
}

int main(int argc, char *argv[])
{ 
    TipoFila Fila;
    char NomeArquivo[20];

    printf("Digite o nome do arquivo: ");
    scanf("%s", NomeArquivo);

    FFVazia(&Fila);

    LerArquivo(NomeArquivo, &Fila);
    
    return 0;
}
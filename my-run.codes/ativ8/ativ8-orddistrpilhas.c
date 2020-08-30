#include <stdio.h>
#include <stdlib.h>

typedef char TipoChave[100];

typedef struct {
  TipoChave Nome;
  int Nota;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Fundo, Topo;
  int Tamanho;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{ Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Fundo = Pilha->Topo;
  Pilha->Topo->Prox = NULL;
  Pilha->Tamanho = 0;
} 

int Vazia(TipoPilha Pilha)
{ return (Pilha.Topo == Pilha.Fundo); } 

void Empilha(TipoItem x, TipoPilha *Pilha)
{ TipoApontador Aux;
  Aux = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Topo->Item = x;
  Aux->Prox = Pilha->Topo;
  Pilha->Topo = Aux;
  Pilha->Tamanho++;
} 

void Desempilha(TipoPilha *Pilha, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Pilha)) { printf("Erro: lista vazia\n"); return; }
  q = Pilha->Topo;
  Pilha->Topo = q->Prox;
  *Item = q->Prox->Item;
  free(q);  Pilha->Tamanho--;
} 

int Tamanho(TipoPilha Pilha)
{ return (Pilha.Tamanho); } 

void CarregarArquivo(char NomeArq[], TipoPilha *Pilha) {

  FILE *Arq;
  TipoItem *Item;
  int i, NumItem;

  Arq = fopen(NomeArq, "rb");

  /* Caso ocorra algum erro na abertura do arquivo */
  if (Arq == NULL) {
    printf("Erro! Impossivel abrir o arquivo!\n");
    exit(1);
  }

  /* Lê o numero de itens do arquivo */
  fseek(Arq, 0, SEEK_END);
  NumItem = ftell(Arq) / sizeof(TipoItem);
  rewind(Arq);  

  Item = (TipoItem *) malloc(NumItem * sizeof(TipoItem));

  fread(Item, sizeof(TipoItem), NumItem, Arq);

  fclose(Arq);

  /* Empilha item a item */
  for (i=0; i<NumItem; i++)
    Empilha(Item[i], Pilha);
}

void Bucketsort(TipoPilha *Pilha, TipoPilha PilhaBucket[]) {

  TipoItem Item;
  int i, TAM;

  TAM = Tamanho(*Pilha);

  for (i=0; i<TAM; i++) {
    Desempilha(Pilha, &Item);
    Empilha(Item, &PilhaBucket[Item.Nota]);
  }

}

int main() {  

  char NomeArq[20];

  TipoPilha Pilha, PilhaBucket[11];
  TipoItem Item;
  int i;

  /* Leitura do nome do arquivo */
  printf("Digite o nome do arquivo: ");
  scanf("%s", NomeArq);

  /* Inicializa pilhas */
  FPVazia(&Pilha);
  for(i=0; i<11; i++)
    FPVazia(&PilhaBucket[i]);

  CarregarArquivo(NomeArq, &Pilha);

  Bucketsort(&Pilha, PilhaBucket);

  /* Nova linha antes da impressão do resultado */
  printf ("\n");

  /* Impressao dos nomes e das notas */
  for (i=0; i<11; i++) {
    while (!Vazia(PilhaBucket[i])) {
      Desempilha(&PilhaBucket[i], &Item);
      printf ("%s\n", Item.Nome);
      printf ("%d\n", Item.Nota);      
    }
  }

  return(0);
}


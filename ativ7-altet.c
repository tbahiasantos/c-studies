#include <stdio.h>

#define MAXTAM          70
#define CANCELAPALAVRA  '$'
#define CANCELACARATER  '#'
#define CANCELALINHA    '\\'
#define SALTALINHA      '*'
#define MARCAEOF        '~'

typedef char TipoChave;

typedef int TipoApontador;

typedef struct {
  /* --- outros componentes --- */
  TipoChave Chave;
} TipoItem;

typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Topo;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{ Pilha->Topo = 0;
}  /* FPVazia */

int Vazia(TipoPilha Pilha)
{ return (Pilha.Topo == 0);
}  /* Vazia */

void Empilha(TipoItem x, TipoPilha *Pilha)
{ if (Pilha->Topo == MAXTAM)
  printf(" Erro   pilha est  a  cheia\n");
  else { Pilha->Topo++;
         Pilha->Item[Pilha->Topo - 1] = x;
       }
}  /* Empilha */

void Desempilha(TipoPilha *Pilha, TipoItem *Item)
{ if (Vazia(*Pilha)) 
  printf(" Erro   pilha est  a  vazia\n");
  else { *Item = Pilha->Item[Pilha->Topo - 1];
         Pilha->Topo--;
       }
}  /* Desempilha */

int Tamanho(TipoPilha Pilha)
{ return (Pilha.Topo);
}  /* Tamanho */

void Imprime(TipoPilha *Pilha)
{ TipoPilha Pilhaux;
  TipoItem x;
  FPVazia(&Pilhaux);
  while (!Vazia(*Pilha)) 
  { Desempilha(Pilha, &x); Empilha(x, &Pilhaux); 
  }
  while (!Vazia(Pilhaux)) 
  { Desempilha(&Pilhaux, &x); putchar(x.Chave); 
  }
  putchar('\n');
} 

int main(int argc, char *argv[])
{ TipoPilha Pilha;
  TipoItem x;
  FPVazia(&Pilha);
  x.Chave = getchar();
  if (x.Chave == '\n') x.Chave = ' ';
  while (x.Chave != MARCAEOF) 
  { if (x.Chave == CANCELAPALAVRA)
    { if (!Vazia(Pilha))
      { while (x.Chave != ' ')
        {  Desempilha(&Pilha, &x);
        }
      }
    }
    else if (x.Chave == CANCELACARATER) 
    { if (!Vazia(Pilha)) Desempilha(&Pilha, &x);
    }   
    else if (x.Chave == CANCELALINHA) 
         FPVazia(&Pilha);
         else if (x.Chave == SALTALINHA) 
              Imprime(&Pilha);
              else { if (Tamanho(Pilha) == MAXTAM) Imprime(&Pilha);
                     Empilha(x, &Pilha);
                   }
    x.Chave = getchar();
    if (x.Chave == '\n') x.Chave = ' ';
  }
  if (!Vazia(Pilha)) Imprime(&Pilha);
  return 0;
} 

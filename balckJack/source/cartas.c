#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h" 
#include "Pilha.h" 
#include "iteradores.h"

#include "logica.h"
#include "cartas.h"
#include "graficos.h"

dado construtor(char suite, int peso){
    dado carta;
    carta.naipe = suite;
    carta.valor = peso;
 return carta;
 }

void numerosAleatorios(int *arr, int maximo, int minimo){
  int numero, inc = 0, i = 0, clt;

  while(inc < maximo){
    numero = ((rand() % (maximo - minimo +1)) + minimo); 
    
    for(i = 0; i <= inc; i++){
        if(arr[i] == numero){
          clt = 0;
          break;
        }
        else if(arr[i] != numero){
          clt = 1;
        }
    }
    if(clt == 1){
      arr[inc]=numero;
      inc++;
    }
  }
}

/* funcao distribui_cartas da uma carta para o jogador e uma para o dealer,
mesmo comportamento da funcao distribui_carta essa porem so fornece uma carta
por vez a quem solicitar.
*/

int distribui_cartas(pilha *p1, pilha *p2, dado var, iterador auxiliar, int *sum, int *sum2, int *ace, int *ace2){
  int aux;
   var = elemento(auxiliar);
   if(var.valor == 14){*ace += 1;}

   insere(p1, var);
   soma_cartas(var, sum, ace);
   aux = *sum2;
   proximo(&auxiliar);

   var = elemento(auxiliar);
   if(var.valor == 14){*ace2 += 1;}
   insere(p2, var);
   soma_cartas(var, sum2, ace2);

   return aux;
}

dado distribui_carta(pilha *Pilha, dado var, iterador auxiliar, int *soma, int *as){
   var = elemento(auxiliar);
   if(var.valor == 14){*as += 1;}
   soma_cartas(var, soma, as);
   insere(Pilha, var);
  return var;
}

iterador removerDois(lista *baralho){
   iterador aux;
   removerInicio(baralho);
   removerInicio(baralho);
   return aux = primeiro(baralho);
}

iterador removerUm(lista *baralho){
   iterador aux;
   removerInicio(baralho);
   return aux = primeiro(baralho);
}


/* shuffle recebe como parametros quatro vetores que contem numeros de 1 a 14 
em ordem aleatoria e um vetor chave que contem numeros de 1 a 56 em ordem 
tambem aleatoria. Dentro da funcao um comando for varre o vetor chave e
de acordo com o valor obtido decide qual sera a carta inserida na lista.
*/

void shuffle(int *copas, int *ouros, int *paus, int *espadas, int *chave, lista baralho){
    int i = 0, j = 0, k = 0, l = 0, m = 0;  
    dado aux;

    int rand_num = chave[i];
  
      for(int i = 1; i <= 56; i++){
      if(rand_num <= 14){
        aux = construtor(COPAS, copas[j++]);
        if(aux.valor > 1){inserirInicio(&baralho, aux);}}

      if(rand_num > 14 && rand_num <= 28){
        aux = construtor(OUROS, ouros[k++]);
        if(aux.valor > 1 && aux.valor < 15){inserirInicio(&baralho, aux);}}

      if(rand_num > 28 && rand_num <= 42){
        aux = construtor(PAUS, paus[l++]);
        if(aux.valor > 1 && aux.valor < 15){inserirInicio(&baralho, aux);}}
      
      if(rand_num > 42 && rand_num <= 56){
        aux = construtor(ESPADAS, espadas[m++]);
        if(aux.valor > 1 && aux.valor < 15){inserirInicio(&baralho, aux);}}
      aux.valor = 0;
  
      rand_num = chave[i];
    }
}


void inicializaBaralho(lista *baralho){
  int copas[MAX], ouros[MAX], paus[MAX], espadas[MAX], chave[MAXCARTAS];

   time_t t;
    srand(time(&t)); 
    numerosAleatorios(copas, rangeMAX, rangeMIN);
    numerosAleatorios(ouros, rangeMAX, rangeMIN);
    numerosAleatorios(paus, rangeMAX, rangeMIN);
    numerosAleatorios(espadas, rangeMAX, rangeMIN);
    numerosAleatorios(chave, MAXCARTAS, rangeMIN);

    shuffle(copas, ouros, paus, espadas, chave, *baralho);
}


void VerifyBlackjack(int sum, int sum2, int *ctlVic, int *banco){
   if(blackjack(sum, sum2, *ctlVic, *banco) == 1){
                printf("vitoria B\n");
                *ctlVic = -1;
            }
            if(blackjack(sum, sum2, *ctlVic, *banco) == 2){
                printf("Derrota B\n");
                *ctlVic = -2;
            }
            if(blackjack(sum, sum2, *ctlVic, *banco) == 3){
                printf("Empate B\n");
                *ctlVic = -3;   
            }
}

void VerifyHit(int sum, int sum2, int *ctlVic, int *banco){
  if(blackjackHit(sum, sum2, *ctlVic, *banco) == 1){
                printf("vitoria H\n");
                *ctlVic = -1;
            }
            if(blackjackHit(sum, sum2, *ctlVic, *banco) == 2){
                printf("Derrota H\n");
                *ctlVic = -2;
            }
}

void VerifyStand(int sum, int sum2, int *ctlVic, int *banco){
   if(vitoriaSdl(sum, sum2, *ctlVic, *banco) == 1){
                printf("vitoria S\n");
                *ctlVic = -1;
            }
             if(vitoriaSdl(sum, sum2, *ctlVic, *banco) == 2){
                printf("Derrota S\n");
                *ctlVic = -2;
            }
              if(vitoriaSdl(sum, sum2, *ctlVic, *banco) == 3){
                printf("Empate S\n");
                *ctlVic = -3;
            }
}


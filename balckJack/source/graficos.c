#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>

#include "graficos.h"

int trasVar(dado data){
  int sum = 0;
  if(data.valor == 11|| data.valor == 12 || data.valor == 13 || data.valor == 14){
    data.valor = 10;
  }
  sum = data.valor;
  return sum;
}

int blackjack(int sum, int sum2, int contr, int banco){
  if(sum == 20 && sum2 < 20 && contr == 0){
        printf("\njogador venceu +\n");
        contr = 1;
        banco++;
        printf("saldo: %d$\n", banco);
      }

     if(sum2 > 17 && sum < sum2 && contr == 0){
        printf("\njogador perdeu *\n");
        contr = 2;
        banco--;
        printf("saldo: %d$\n", banco);
      }

      if(sum2 < 22 && sum2 == sum && contr == 0){
        printf("\nempate\n");
        contr = 3;
        banco++;
        printf("saldo: %d$\n", banco);
      }
  return contr;
}

int blackjackHit(int sum, int sum2, int contr, int banco){
    if(sum == 21 && contr == 0){
        printf("\njogador venceu HIT\n");
        contr = 1;
        banco++;
        printf("saldo: %d$\n", banco);
      }

      if(sum > 21 && contr == 0){
        printf("\njogador perdeu Hit\n");
        contr = 2;
        banco--;
        printf("saldo: %d$\n", banco);
      }
    return contr;
}

int vitoriaSdl(int sum, int sum2, int contr, int banco){

     if(sum > 17 && sum < 21 && sum == sum2 && contr == 0){
        printf("\nempate\n");
        contr = 3;
        banco++;
        printf("saldo: %d$\n", banco);
      }

     if(sum2 > sum && sum2 <= 21 && contr == 0){
        printf("\njogador perdeu $\n");
        contr = 2;
        banco--;
        printf("saldo: %d$\n", banco);
      }

    if(sum2 > 21 || (sum > sum2 && sum2 > 17)){
        printf("\njogador venceu!\n");
        contr = 1;
        banco++;
        printf("saldo: %d$\n", banco);
      }
  return contr;
}

void dimencao(SDL_Rect *rect, SDL_Surface *surface, int x, int y){
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;
}

void dimencaoCompleta(SDL_Rect *rect, int x, int y, int w, int h){
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void printCard(dado item2){
          if(item2.valor != 11 && item2.valor != 12 && item2.valor != 13  && item2.valor != 14){
          printf("|%c %2d| ", item2.naipe, item2.valor);}
          if(item2.valor == 11){printf("|%c  J| ", item2.naipe);}
          if(item2.valor == 12){printf("|%c  Q| ", item2.naipe);}
          if(item2.valor == 13){printf("|%c  K| ", item2.naipe);}
          if(item2.valor == 14){printf("|%c  A| ", item2.naipe);} 
}

void pilha_jogador(pilha *p1, pilha *p2) {
     pilha pp  = *p1;
     pilha pp2 = *p2;

     printf("=======================================\n");

     dado item1, item2;

      while(pp2.topo != 0){                       
           if(pp2.topo != 0){
               item2 = pp2.v[pp2.topo-1];
               printCard(item2);
               pp2.topo--;}
      }
      printf("\n\n");
      while(pp.topo != 0){
          if(pp.topo != 0){
               item1 = pp.v[pp.topo-1];
               printCard(item1);
               pp.topo--;}
     }
     printf("\n\n");
}

void pilha_dealer(pilha *p1, pilha *p2) {
   pilha pp  = *p1;
   pilha pp2 = *p2;
   dado item1, item2;

     printf("=======================================\n");

       if(pp2.topo != 0){
           pp2.topo--;
           item2 = pp2.v[pp2.topo-1];
           printf("|####| ");
           printCard(item2);
       }

       printf("\n\n");

       while(pp.topo != 0){
          if(pp.topo != 0){
               item1 = pp.v[pp.topo-1];
               printCard(item1);
               pp.topo--;
          }
         
       }
     printf("\n\n");
}

void gameStats(int *soma_player, int *soma_dealer, int *banco){
      printf("%.2d dealer\n", *soma_dealer);
      printf("%.2d jogador                %d banco\n", *soma_player, *banco);
   
      printf("=======================================\n\n");
  
}


void cabecalho(){
     printf("\n  *** BLACKJACK ***\n\n");
}

void fimRodada(){
     printf("Digite 1 para continuar e 0 para sair: ");
}

void jogadas(){
     blue();
     printf("jogada: ");
     neutro();
}

void movimentoInvalido(){
     printf("Movimento invalido\n");
}

void vitoria(int banco){
     yellow();
     printf("\njogador venceu\n");
     neutro();
     printf("saldo: %d$\n\n", banco);
}

void empate(int banco){
     printf("\nempate\n");
     printf("saldo: %d$\n\n", banco);
}

void derrota(int banco){
     red();
     printf("\njogador perdeu\n");
     neutro();
     printf("saldo: %d$\n\n", banco);
}
void saldo(int banco){
     printf("saldo: %d$\n", banco);
}

void fimDeJogo(int banco){
     blue();
     printf("\n=======================================\n");
     printf("\nfim de jogo\n\n");
     printf("saldo final: %d\n", banco);
     printf("\n=======================================\n");
     neutro();
}

void red(){
  printf("\033[1;31m");
}
void blue(){
  printf("\033[1;34m");
}
void green(){
  printf("\033[1;32m");
}
void yellow(){
  printf("\033[0;33m");
}
void neutro(){
  printf("\033[0m");
}


#ifndef GRAFICOS_H
#define GRAFICOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "pilha.h" 
#include "lista.h" 

typedef struct stats{
    int ace, ace2, stand;
} stats;


int trasVar(dado data);
int blackjack(int sum, int sum2, int contr, int banco);
int blackjackHit(int sum, int sum2, int contr, int banco);
int vitoriaSdl(int sum, int sum2, int contr, int banco);
void dimencao(SDL_Rect *rect, SDL_Surface *surface, int x, int y);
void dimencaoCompleta(SDL_Rect *rect, int x, int y, int w, int h);

void gameStats(int *soma_player, int *soma_dealer, int *banco);
void pilha_jogador(pilha *p1, pilha *p2);
void pilha_dealer(pilha *p1, pilha *p2);
void printCard(dado item2);


void red();
void green();
void blue();
void yellow();
void neutro();

void cabecalho();
void fimRodada();
void jogadas();
void movimentoInvalido();

void vitoria(int banco);
void derrota(int banco);
void empate(int banco);
void saldo(int banco);

void fimDeJogo(int banco);



#endif
#ifndef CARTAS_H
#define CARTAS_H
#include "cartas.h"
#include "pilha.h" 
#include "iteradores.h" 

#define MAX 14
#define rangeMAX 14
#define rangeMIN 1
#define MAXCARTAS 56

#define COPAS 3
#define OUROS 4
#define ESPADAS 6
#define PAUS 5


iterador removerUm(lista *primos);
iterador removerDois(lista *primos);


void shuffle(int copas[], int ouros[], int paus[], int espadas[], int chave[], lista primos);
dado construtor(char suite, int peso);

void inicializaBaralho(lista *baralho);
void reinsere(pilha *p1, lista primos);

void VerifyBlackjack(int sum, int sum2, int *ctlVic, int *banco);
void VerifyHit(int sum, int sum2, int *ctlVic, int *banco);
void VerifyStand(int sum, int sum2, int *ctlVic, int *banco);


int distribui_cartas(pilha *p1, pilha *p2, dado var, iterador auxiliar, int *sum, int *sum2, int *ace, int *ace2);
dado distribui_carta(pilha *Pilha, dado var, iterador auxiliar, int *soma, int *as);

iterador removerDois(lista *baralho);
iterador removerUm(lista *baralho);

#endif


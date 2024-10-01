#ifndef PILHA_H
#define PILHA_H
#include "lista.h"

#define TAMANHO_MAXIMO_PILHA 100

struct pilha_ {
    unsigned topo;
    dado *v;
};
typedef struct pilha_ pilha;


pilha cria(unsigned tamanho_maximo);
void destroi(pilha *p);
int vazia(pilha *p);
int cheia(pilha *p);
unsigned tamanho(pilha *p);
void insere(pilha *p, dado item);
void retira(pilha *p);
int topo(pilha *p, dado *item);

void esvazia(pilha *p);



#endif
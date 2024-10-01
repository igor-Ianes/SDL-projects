#include <stdio.h>
#include <stdlib.h>
#include "pilha.h" 
#include "lista.h" 

pilha cria(unsigned tamanho_maximo) {
     pilha *stack = (pilha*)malloc(sizeof(struct pilha_));
     stack->topo = 0;
     stack->v = (dado*)malloc(tamanho_maximo * sizeof(T));
  return *stack;
}

void destroi(pilha *p) {
free(p->v);
p->v = NULL;
p->topo = 0;
}

void inicializa(pilha *p) {
          p->topo = 0;
}

int vazia(pilha *p) {
          return p->topo == 0;
}

int cheia(pilha *p) {
          return p->topo == TAMANHO_MAXIMO_PILHA;
}

unsigned tamanho(pilha *p) {
          return p->topo;
}

void insere(pilha *p, dado item) {
     if( !cheia(p) ) {
        p->v[p->topo] = item;
        p->topo++;
      }
}

void retira(pilha *p) {
     if( !vazia(p) ) {
        p->topo--;
     }
}

int topo(pilha *p, dado *item) {
    if( !vazia(p) ) {
         *item = p->v[p->topo-1];
         return 1;
     }

return 0;
}


void esvazia(pilha *p) {
     while( !vazia(p) ) {
        retira(p);
     }
}

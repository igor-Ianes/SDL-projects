#include <stdio.h>
#include <stdlib.h>
#include "lista.h" 

void inicializar( lista *p ) {
    struct node *n = (node*)malloc(sizeof(struct node));
    n->next = n->prev = p->sentinela = n;
    p->quantidade = 0;
}

int vaziaL( lista *p ) {
   return p->sentinela->next == p -> sentinela;
}

void inserirInicio( lista *p, dado data) {
    struct node *n = (node*)malloc(sizeof(struct node));
    n->data = data;
    n->next = p->sentinela->next;
    n->prev = p->sentinela;
    p->sentinela->next = n;
    n->next->prev = n;
    p->quantidade++;
}

void inserirFim( lista *p, dado data) {
    struct node *n = (node*)malloc(sizeof(struct node));
    n->data = data;
    n->prev = p->sentinela->prev;
    n->next = p->sentinela;
    p->sentinela->prev = n;
    n->prev->next = n;
    p->quantidade++;
}

void removerFim( lista *p) {
   struct node *n = p->sentinela->prev;
   if( n != p->sentinela ) {
     n->next->prev = n->prev;
     n->prev->next = n->next;
     free(n);
     p->quantidade--;
    }
}

void removerInicio( lista *p) {
   struct node *n = p->sentinela->next;
   if( n != p->sentinela ) {
     n->prev->next = n->next;
     n->next->prev = n->prev;
     free(n);
     p->quantidade--;
    }
}

void destruir( lista *p ) {
   while(!vaziaL(p))
   removerInicio(p);
   free(p->sentinela);
}

#ifndef LISTA_H
#define LISTA_H

typedef char T;

typedef struct dado{
    T naipe;
    int valor;
} dado;

typedef struct node{
    dado data;
    struct node *next, *prev;
} node;
 
typedef struct {
    struct node *sentinela;
    unsigned quantidade;
} lista;

void inicializar( lista *p );
int vaziaL( lista *p );
void inserirInicio( lista *p, dado data);
void inserirFim( lista *p, dado data);
void removerFim( lista *p);
void removerInicio( lista *p);
void destruir( lista *p );

#endif
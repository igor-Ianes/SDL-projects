#ifndef ITERADORES_H
#define ITERADORES_H
#include "lista.h"

typedef struct {
    struct node *posicao;
    lista *estrutura;
} iterador;

iterador primeiro( lista* l );
iterador ultimo( lista* l );

int acabou( iterador i );
int elementov( iterador i, dado* data );
dado elemento( iterador i );
int proximo( iterador* i );

#endif
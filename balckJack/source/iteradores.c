
#include <stdio.h>
#include <stdlib.h>
#include "lista.h" 
#include "iteradores.h" 

iterador primeiro( lista* l ) {
    iterador i;
    i.posicao = l->sentinela->next;
    i.estrutura = l;
  return i;
}

iterador ultimo( lista* l ) {
    iterador i;
    i.posicao = l->sentinela->prev;
    i.estrutura = l;
 return i;
}

int acabou( iterador i ) {
    return i.posicao == i.estrutura->sentinela;
}

int elementov( iterador i, dado* data ) {
    if( !acabou( i ) ) {
        *data = i.posicao->data;
         return 1;
     }
    return 0;
}

dado elemento( iterador i ) {
    return i.posicao->data;
}

int proximo( iterador* i ) {
    if( !acabou( *i ) ) {
        i->posicao = i->posicao->next;
        return 1;
    }
    return 0;
}
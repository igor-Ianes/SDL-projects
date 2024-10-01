#ifndef LOGICA_H
#define LOGICA_H

#include "cartas.h"
#include "pilha.h" 
#include "iteradores.h" 
#include "graficos.h"

dado soma_cartas(dado data, int *sum, int *as);

void blackJackVerify(int sum, int sum2, int *banco, int *control);
void fiveVerify(int soma, int five, int *banco, int *control);
void hitVerify(int sum, int sum2, int *banco, int *control);
void standVerify(int sum, int sum2, int *banco, int *control);
void reinsere(pilha *p1, lista primos);

#endif

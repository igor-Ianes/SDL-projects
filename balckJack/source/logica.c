#include "lista.h" 
#include "pilha.h" 
#include "iteradores.h"

#include "logica.h"
#include "cartas.h"
#include "graficos.h"

/*soma_cartas recebe como parametro a carta, a variavel do somatorio
e um contador de as, para que caso o valor seja superior a 21 oa ases
sejam convertidos de 11 para 1*/

dado soma_cartas(dado data, int *soma_player, int *as){
      if(data.valor ==11|| data.valor == 12 || data.valor == 13){
         data.valor = 10;
      }
      if( data.valor == 14){
        data.valor = 11;
      }

      *soma_player += data.valor;

      while (*as > 0 && *soma_player > 21){
          *soma_player -= 10;
          *as  -= 1;
      }
  return data;
}

void reinsere(pilha *p1, lista primos){  
  dado item = p1->v[p1->topo - 1];
  inserirFim(&primos, item);  
  retira(p1);                     
}

/*funcoes jogada tem comportamento parecido e controlam o andamento do jogo
sendo que, distribuem cartas, retiram cartas da lista e printam as cartas
*/

void jogada01(lista baralho, pilha *p1, pilha *p2, iterador *auxiliar, int *soma_player, int *soma_dealer, int *banco, stats *game){
      dado var;
      distribui_cartas(p1, p2, var, *auxiliar, soma_player, soma_dealer, &game->ace, &game->ace2);
      *auxiliar = removerDois(&baralho);

      game->stand = distribui_cartas(p1, p2, var, *auxiliar, soma_player, soma_dealer, &game->ace, &game->ace2);
      pilha_dealer(p1, p2);
      *auxiliar = removerDois(&baralho);
      gameStats(soma_player, &game->stand, banco);
} 

void jogada02(lista baralho, pilha *p1,  pilha *p2, iterador *auxiliar, int *soma_player, int *soma_dealer, int *banco, stats *game){
       dado var;
       distribui_carta(p1, var, *auxiliar, soma_player, &game->ace);
       pilha_dealer(p1, p2);
      *auxiliar = removerUm(&baralho);
       gameStats(soma_player, &game->stand, banco);
} 

void jogada03(lista baralho,  pilha *p1, pilha *p2, iterador *auxiliar, int *soma_player, int *soma_dealer, int *banco, stats *game){
       dado var;
       distribui_carta(p2, var, *auxiliar, soma_dealer, &game->ace2);
       pilha_jogador(p1, p2);
      *auxiliar = removerUm(&baralho);
       gameStats(soma_player, soma_dealer, banco);
} 

/*funcoes  verify verificam a soma das cartas e atualizam o status da rodada*/

void blackJackVerify(int soma_player, int soma_dealer, int *banco, int *control){
    if(soma_player == 21 && *control == 0){
        *control = -1;
        *banco += 1;
        vitoria(*banco);   
      }
}

void fiveVerify(int soma, int five, int *banco, int *control){
    if(soma <= 21 && five == 2 && *control == 0){
        *control = -1;
        *banco += 1;
        vitoria(*banco);
      }
}

void hitVerify(int soma_player, int soma_dealer, int *banco, int *control){
    if(soma_player == 21 && *control == 0){
        *control = -1;
        *banco += 1;
        vitoria(*banco);
      }

      if(soma_player > 21 && *control == 0){
        *control = -2;
        *banco -= 1;
        derrota(*banco); 
      }
}

void standVerify(int soma_player, int soma_dealer, int *banco, int *control){
     if(soma_player == 21 && soma_dealer == 21 && *control == 0){
        *control = -3;
        *banco += 1;
        empate(*banco); 
      }

      if(soma_player == soma_dealer && soma_dealer >= 18 && *control == 0){
        *control = -3;
        *banco += 1;
        empate(*banco);  
      }

     if(soma_dealer > soma_player && soma_dealer <= 21 && *control == 0){
        *control = -2;
        *banco -= 1;
        derrota(*banco);
      }

    if(((soma_dealer > 21) || (soma_player > soma_dealer)) && (*control == 0)){
        *control = -1;
        *banco += 1;
        vitoria(*banco); 
      }
}

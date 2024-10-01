#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "lista.h" 
#include "pilha.h" 
#include "iteradores.h" 

#include "logica.h"
#include "pacote.h" 
#include "cartas.h"
#include "graficos.h"

#define FICHAS 10

typedef struct {
    SDL_Rect draw_rect;    // dimensions of button
    struct {
        Uint8 r, g, b, a;
    } colour;

    bool pressed;
} button_t;

static void button_process_event(button_t *btn, const SDL_Event *ev) {
    // react on mouse click within button rectangle by setting 'pressed'
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= btn->draw_rect.x &&
                ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
                ev->button.y >= btn->draw_rect.y &&
                ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
            btn->pressed = true;
        }
    }
}

static bool button(SDL_Renderer *r, button_t *btn) {
    // draw button
    SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
    SDL_RenderFillRect(r, &btn->draw_rect);

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}


int main (int argc, char *argv[]){

    int quit = 0;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = NULL;

    window = SDL_CreateWindow("",350, 150, 800, 500,    SDL_WINDOW_SHOWN);
    if (window == NULL){
        fprintf(stderr, "create window failed: %s\n", SDL_GetError());
        return 1;   // 'error' return status is !0. 1 is good enough
    }

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {   // renderer creation may fail too
        fprintf(stderr, "create renderer failed: %s\n", SDL_GetError());
        return 1;
    }

     SDL_Surface * iconeS = SDL_LoadBMP(ICONE);
     SDL_SetWindowIcon(window, iconeS);

    //variaveis para manipulacao das imagens

    SDL_Surface *titulo;
    titulo = SDL_LoadBMP(TITULO);
    SDL_Texture *tituloLogo;
    tituloLogo = SDL_CreateTextureFromSurface(renderer, titulo);
    SDL_Rect tituloRect;
    dimencao(&tituloRect, titulo, 1, 1);

    SDL_Surface *RotuloStand;
    RotuloStand = SDL_LoadBMP(STAND);
    SDL_Texture *StandLogo;
    StandLogo = SDL_CreateTextureFromSurface(renderer, RotuloStand);
    SDL_Rect StandRect;
    dimencao(&StandRect, RotuloStand, 550, 183);

    SDL_Surface *RotuloHIT;
    RotuloHIT = SDL_LoadBMP(HIT);
    SDL_Texture *HITLogo;
    HITLogo = SDL_CreateTextureFromSurface(renderer, RotuloHIT);
    SDL_Rect HITRect;
    dimencao(&HITRect, RotuloHIT, 70, 183);

    SDL_Surface *Vitoria;
    Vitoria = SDL_LoadBMP(VIC);
    SDL_Texture *VitoriaLogo;
    VitoriaLogo = SDL_CreateTextureFromSurface(renderer, Vitoria);
    SDL_Rect VitoriaRect;
    dimencao(&VitoriaRect, Vitoria, 300, 200);

    SDL_Surface *Derrota;
    Derrota = SDL_LoadBMP(DEF);
    SDL_Texture *DerrotaLogo;
    DerrotaLogo = SDL_CreateTextureFromSurface(renderer, Derrota);
    SDL_Rect DerrotaRect;
    dimencao(&DerrotaRect, Derrota, 300, 200);



    SDL_Surface *regras;
    regras = SDL_LoadBMP(REG);
    SDL_Texture *regrasLogo;
    regrasLogo = SDL_CreateTextureFromSurface(renderer, regras);
    SDL_Rect regrasRect;
    dimencao(&regrasRect, regras, 150, 100);

    SDL_Surface *regrasB;
    regrasB = SDL_LoadBMP(REGB);
    SDL_Texture *regrasLogoB;
    regrasLogoB = SDL_CreateTextureFromSurface(renderer, regrasB);
    SDL_Rect regrasRectB;
    dimencao(&regrasRectB, regrasB, 620, 425);

    SDL_Surface *scores;
    scores = SDL_LoadBMP(RES);
    SDL_Texture *scoresLogo;
    scoresLogo = SDL_CreateTextureFromSurface(renderer, scores);
    SDL_Rect scoresRect;
    dimencao(&scoresRect, scores, 270, 100);




    SDL_Surface *surface,  *surface2, *surface3, *surface4, *surface5;
    SDL_Surface *surface6, *surface7, *surface8, *surface9, *surface10;
    
    SDL_Texture *logo, *logo2, *logo3, *logo4, *logo5;
    SDL_Texture *logo6, *logo7, *logo8, *logo9, *logo10;

    SDL_Rect rect,  rect2, rect3, rect4, rect5;
    SDL_Rect rect6, rect7, rect8, rect9, rect10;

    
    //armazena temporariamente as strings que serao exibidas
    char buffer[50], buffer2[50], buffer3[50], buffer4[50];
    
    /*
    inicializa a fonte a ser utilizada pela biblioteca TFF
    e inicializa variaveis para control_HITe de cor das fontes
    */
    TTF_Font* Sans = TTF_OpenFont("fontes/arial.ttf", 24);
    SDL_Color White = {255, 255, 255};
    SDL_Color Black = {0, 0, 0};

    //declaracao e configuracao das saidas de texto
    SDL_Surface* surfaceMessage;
    surfaceMessage =TTF_RenderText_Solid(Sans, "cash", Black); 
    SDL_Texture* Message;
    SDL_Rect Message_rect; //create a rect
    //dimencao(&Message_rect, surfaceMessage, 20, 450);
    dimencaoCompleta(&Message_rect, 20, 450, 70, 40);

    SDL_Surface* surfaceMessage2;
    surfaceMessage2 =TTF_RenderText_Solid(Sans, "Dealer", White); 
    SDL_Texture* Message2;
    SDL_Rect Message_rect2; //create a rect
    dimencao(&Message_rect2, surfaceMessage2, 650, 20);
   

    SDL_Surface* surfaceMessage3;
    surfaceMessage3 =TTF_RenderText_Solid(Sans, "Player", White); 
    SDL_Texture* Message3;
    SDL_Rect Message_rect3; //create a rect
    dimencao(&Message_rect3, surfaceMessage3, 650, 350);

    SDL_Surface* surfaceMessage4;
    surfaceMessage4 =TTF_RenderText_Solid(Sans, "Start", Black); 
    SDL_Texture* Message4;
    Message4 = SDL_CreateTextureFromSurface(renderer, surfaceMessage4);
    SDL_Rect Message_rect4; //create a rect
    dimencaoCompleta(&Message_rect4, 300, 180, 200, 80);

    SDL_Surface* surfaceMessage5;
    surfaceMessage5 =TTF_RenderText_Solid(Sans, "Hit", Black); 
    SDL_Texture* Message5;
    Message5 = SDL_CreateTextureFromSurface(renderer, surfaceMessage5);
    SDL_Rect Message_rect5; //create a rect
    dimencaoCompleta(&Message_rect5, 90, 190, 100, 50);

    SDL_Surface* surfaceMessage6;
    surfaceMessage6 =TTF_RenderText_Solid(Sans, "Stand", Black); 
    SDL_Texture* Message6;
    Message6 = SDL_CreateTextureFromSurface(renderer, surfaceMessage6);
    SDL_Rect Message_rect6; //create a rect
    dimencaoCompleta(&Message_rect6, 570, 190, 100, 50);

    SDL_Surface* surfaceMessage7;
    surfaceMessage7 =TTF_RenderText_Solid(Sans, "BLACK JACK", Black); 
    SDL_Texture* Message7;
    Message7 = SDL_CreateTextureFromSurface(renderer, surfaceMessage7);
    SDL_Rect Message_rect7; //create a rect
    dimencaoCompleta(&Message_rect7, 360, 220, 70, 40);

    // button state - colour and rectangle
    button_t start_button = {
        .colour = { .r = 127, .g = 255, .b = 0, .a = 1, },
        .draw_rect = { .x = 300, .y = 180, .w = 200, .h = 100 },
    };

    button_t game_button = {
        .colour = { .r = 255, .g = 0, .b = 0, .a = 1, },
        .draw_rect = { .x = 300, .y = 200, .w = 200, .h = 50 },
    };

     button_t game_button2 = {
        .colour = { .r = 20, .g = 255, .b = 0, .a = 150, },
        .draw_rect = { .x = 550, .y = 190, .w = 180, .h = 55 },
    };

     button_t game_button3 = {
        .colour = { .r = 20, .g = 255, .b = 0, .a = 150, },
        .draw_rect = { .x = 70, .y = 190, .w = 165, .h = 55 },
    };

     button_t vitory_button = {
        .colour = { .r = 255, .g = 255, .b = 0, .a = 1, },
        .draw_rect = { .x = 300, .y = 260, .w = 200, .h = 50 },
    };

    button_t regras_button = {
        .colour = { .r = 255, .g = 255, .b = 0, .a = 1, },
        .draw_rect = { .x = 625, .y = 425, .w = 125, .h = 50 },
    };
    
    button_t quit_button = {
        .colour = { .r = 200, .g = 255, .b = 0, .a = 1, },
        .draw_rect = { .x = 330, .y = 380, .w = 120, .h = 50 },
    };

    enum {
        STATE_IN_MENU,
        STATE_IN_GAME,
    } state = 0;

    enum {
        GAME_RUN,
        GAME_BUTTON,
        GAME_HIT,
        GAME_STAND,
        GAME_ADD,
    } Gstate = 0;

    /*declaracao do game assincrono*/

    lista baralho;
    pilha p1, p2;
    iterador auxiliar;
    stats game;

     /*control comanda o sinal de vitoria ou derrota e 
    control_cartas verifica se o jogador possui 5 cartas */
   // int soma_player = 0, soma_dealer = 0;
   // int control = 0, control_cartas = 0, continuar = 0;
   // int jogada  = 1, banco = FICHAS;

    /* jogada eh inicializado com 1 pois ao ser executado o jogo
    automaticamente iniciara a rodada inicial, ja banco eh 
    inicializado com o numero de fichas que o jogador tera.*/

    game.ace2  = 0;  // contagem de as do dealer
    game.ace   = 0;  // contagem de as do jogador
    game.stand = 0;  // sinal de controle para stand
   
    int sum = 0, sum2 = 0;
    int banco = 1;

    int bancoCtl = 0;
    int dealerCtl = 0;
    int playCtl = 0;
    int vitoryCtl = 0;
    int trasBanco = 0;
    int gambiarra = 0; // para control_HITar stand dentro da vitoria
    int gambi2 = 0;    // controle do hit nao loop infinito
 
    inicializar(&baralho);

    inicializaBaralho(&baralho);

    auxiliar = primeiro(&baralho);

    dado var, var2, var3, var4, var5;
    dado var6, var7, var8, var9, var10;

    int control_HIT = 0;
    int ctlHit = 0;
    int ctlStand = 0;
    int ctlVic = 0;
    int trasClt = 0;
    int regrasClt = 0;
    int game_Banco = 0; // game button controla score

    int atv1 = 0, atv2 = 0, atv3 = 0, atv4 = 0, atv5 = 0, atv6 = 0, atv7 = 0;

    /*declaracao do game assincrono*/

    while(!quit) {
        SDL_Event evt;    

        // event loop and draw loop are separate things, don't mix them
        while(SDL_PollEvent(&evt)) {
           
            if(evt.type == SDL_QUIT ||
                    (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) ||
                    (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)) {
                quit = 1;
            }
            // pass event to button
            button_process_event(&start_button, &evt);

            button_process_event(&game_button,  &evt);

            button_process_event(&game_button2, &evt);

            button_process_event(&game_button3, &evt);

            button_process_event(&vitory_button, &evt);

            button_process_event(&regras_button, &evt);

            button_process_event(&quit_button, &evt);
        }

        SDL_SetRenderDrawColor(renderer, 127, 220, 0, 200);
        SDL_RenderClear(renderer);
        
        if(state == STATE_IN_MENU) {
            if(button(renderer, &start_button)) {
                printf("Botao START pressionado\n");
                state = STATE_IN_GAME;   // state change - button will not be drawn anymore
            }
             SDL_RenderCopy(renderer, tituloLogo,  NULL, &tituloRect);
        } 
        
        else if(state == STATE_IN_GAME) {
            /* your game logic */

          if(banco == 0 && game_Banco == 1){
             if(button(renderer, &quit_button)) {
              printf("botao quit");
              quit = 1;
             }
            SDL_RenderCopy(renderer, scoresLogo,  NULL, &scoresRect);
            sprintf(buffer4, "Score: %d", game_Banco);
            surfaceMessage7 =TTF_RenderText_Solid(Sans, buffer4, White); 
            Message7 = SDL_CreateTextureFromSurface(renderer, surfaceMessage7);
            SDL_RenderCopy(renderer, Message7, NULL, &Message_rect7);
          }

  if(banco != 0 || game_Banco != 1){
    game_Banco = 0;

              if(button(renderer, &regras_button)) {
                printf("regras\n");
                regrasClt += 1;  
                SDL_RenderCopy(renderer, regrasLogoB,  NULL, &regrasRectB);
                if(regrasClt == 2){regrasClt = 0;}
              }
              if(regrasClt == 1){
                SDL_RenderCopy(renderer, regrasLogo,  NULL, &regrasRect);
              }
                SDL_RenderCopy(renderer, regrasLogoB,  NULL, &regrasRectB);
 
  if(regrasClt == 0){  
          

          if((ctlVic != -1 && ctlVic != -3 && ctlVic != -2)){
            if(button(renderer, &game_button2)) {
                printf("Botao STAND pressionado\n");
                ctlStand = 1;
                trasClt = 1;
                trasBanco = 1;
            }
             SDL_RenderCopy(renderer, Message6, NULL, &Message_rect6);
             SDL_RenderCopy(renderer, StandLogo,  NULL, &StandRect);
          }
          
          if((ctlVic != -1 && ctlVic != -3 && ctlVic != -2)){
            if(button(renderer, &game_button3)) {
                printf("Botao HIT pressionado\n");
                Gstate = GAME_HIT;  
                ctlHit ++;
            }
             SDL_RenderCopy(renderer, Message5, NULL, &Message_rect5);
              SDL_RenderCopy(renderer, HITLogo,  NULL, &HITRect);
          }

          if((ctlVic == -1 || ctlVic == -3) && vitoryCtl == 0) {
              if(button(renderer, &game_button)) {
                if(ctlVic == -1){
                printf("Botao VITORIA pressionado\n");}
                if(ctlVic == -3){
                printf("Botao EMPATE pressionado\n");}
                vitoryCtl = 1; 
                game_Banco = 1;
              }
              SDL_RenderCopy(renderer, VitoriaLogo,  NULL, &VitoriaRect);
          }

          if(ctlVic == -2 && vitoryCtl == 0) {
              if(button(renderer, &game_button)) {
                printf("Botao DERROTA pressionado\n");
                vitoryCtl = 1;  
                game_Banco = 1;
              }
              SDL_RenderCopy(renderer, DerrotaLogo,  NULL, &DerrotaRect);
          }

          game_button.pressed = false;

            if(state == STATE_IN_GAME && control_HIT == 0) {
                printf("Abertura da rodada\n");

                 p1 = cria(100);
                 p2 = cria(100);

                var = distribui_carta(&p2, var, auxiliar, &sum2, &game.ace2);

                auxiliar = removerUm(&baralho);

                var2 = distribui_carta(&p2, var2, auxiliar, &sum2, &game.ace2);

                auxiliar = removerUm(&baralho);

                var3 = distribui_carta(&p1, var3, auxiliar, &sum, &game.ace);
                auxiliar = removerUm(&baralho);

                var4 = distribui_carta(&p1, var4, auxiliar, &sum, &game.ace);
                auxiliar = removerUm(&baralho);

                control_HIT = 1;
                Gstate = GAME_BUTTON;
            }

             if(control_HIT == 1 && ctlHit >=1) {
                printf("HIT UM\n");
                var5 = distribui_carta(&p1, var5, auxiliar, &sum, &game.ace);      
                auxiliar = removerUm(&baralho);
                control_HIT = 2;
             }

             if(control_HIT == 2 && ctlHit >=2) {
                printf("HIT DOIS\n");
                var6 = distribui_carta(&p1, var6, auxiliar, &sum, &game.ace);
                auxiliar = removerUm(&baralho);
                control_HIT = 3;
             }

             if(control_HIT == 3 && ctlHit >=3) {
                printf("HIT TRES\n");
                var7 = distribui_carta(&p1, var7, auxiliar, &sum, &game.ace);
                auxiliar = removerUm(&baralho);
               control_HIT = 4;
             }

             if(ctlStand == 1) {
                printf("STAND 1\n");
                if(sum2 < 18){
                  var8 = distribui_carta(&p1, var8, auxiliar, &sum2, &game.ace2);
                  auxiliar = removerUm(&baralho);
                  ctlStand++;
                }

                if(sum2 < 18){
                  printf("STAND 2\n");
                  var9 = distribui_carta(&p1, var9, auxiliar, &sum2, &game.ace2);
                  auxiliar = removerUm(&baralho);
                  ctlStand++;
                }

                if(sum2 < 18){
                  printf("STAND 3\n");
                  var10 = distribui_carta(&p1, var10, auxiliar, &sum2, &game.ace2);
                  auxiliar = removerUm(&baralho);
                  ctlStand++;
                }
                if(ctlStand == 1){
                    ctlStand = 0;
                }
                gambiarra = 1;
             }

            if(Gstate == 1 || Gstate == 2) {

              if(atv1 == 0 || trasClt == 1){
                 if(trasClt == 0){
                 surface = SDL_LoadBMP(TRAS);}

                 if(trasClt == 1){
                 surface = SDL_LoadBMP(cartas(var.valor, var.naipe));}
                 logo = SDL_CreateTextureFromSurface(renderer, surface);
                 dimencao(&rect, surface, 50, 20);      
    
                surface2 = SDL_LoadBMP(cartas(var2.valor, var2.naipe));
                logo2 = SDL_CreateTextureFromSurface(renderer, surface2);
                dimencao(&rect2, surface, 150, 20);


                surface3 = SDL_LoadBMP(cartas(var3.valor, var3.naipe));
                logo3 = SDL_CreateTextureFromSurface(renderer, surface3);
                dimencao(&rect3, surface,50, 350);

                surface4 = SDL_LoadBMP(cartas(var4.valor, var4.naipe));
                logo4 = SDL_CreateTextureFromSurface(renderer, surface4);
                dimencao(&rect4, surface,150, 350);

                atv1 = 1;
                if(trasClt == 1){trasClt = 2;}
             }   
                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);

             SDL_RenderCopy(renderer, logo,  NULL, &rect);
             SDL_RenderCopy(renderer, logo2, NULL, &rect2); 
             SDL_RenderCopy(renderer, logo3, NULL, &rect3);
             SDL_RenderCopy(renderer, logo4, NULL, &rect4);                    
            }
      
            if(ctlHit >= 2) {
              if(atv2 == 0){
                if(Gstate >= 2){
                surface5 = SDL_LoadBMP(cartas(var6.valor, var6.naipe));}
                logo5 = SDL_CreateTextureFromSurface(renderer, surface5);
                dimencao(&rect5, surface5, 350, 350);
                atv2 = 1;
              }
                SDL_RenderCopy(renderer, logo5,  NULL, &rect5);                
            }
             
             if(ctlHit >=  1) {
               if(atv3 == 0){
                if(Gstate >= 1){
                surface6 = SDL_LoadBMP(cartas(var5.valor, var5.naipe));}
                logo6 = SDL_CreateTextureFromSurface(renderer, surface6);
                dimencao(&rect6, surface6, 250, 350);
                atv3 = 1;
               }
                SDL_RenderCopy(renderer, logo6,  NULL, &rect6);                
             }

            if(ctlHit >= 3) {
               if(atv4 == 0){
                if(Gstate >= 1){
                surface7 = SDL_LoadBMP(cartas(var7.valor, var7.naipe));}
                logo7 = SDL_CreateTextureFromSurface(renderer, surface7);
                dimencao(&rect7, surface7, 450, 350);
                atv4 = 1;
               } 
                SDL_RenderCopy(renderer, logo7,  NULL, &rect7);                
            }

            if(ctlStand >= 1) {
              if(atv5 == 0){
                surface8 = SDL_LoadBMP(cartas(var8.valor, var8.naipe));
                logo8 = SDL_CreateTextureFromSurface(renderer, surface8);
                dimencao(&rect8, surface8, 250, 20);
                atv5 = 1;
              }
                SDL_RenderCopy(renderer, logo8,  NULL, &rect8);                
            }

            if(ctlStand >= 3) {
              if(atv6 == 0){
                surface9 = SDL_LoadBMP(cartas(var9.valor, var9.naipe));
                logo9 = SDL_CreateTextureFromSurface(renderer, surface9);
                dimencao(&rect9, surface9, 350, 20);
                atv6 = 1;
              }
                SDL_RenderCopy(renderer, logo9,  NULL, &rect9);                
            }

            if(ctlStand >= 4) {
             if(atv7 == 0){
                surface10 = SDL_LoadBMP(cartas(var10.valor, var10.naipe));
                logo10 = SDL_CreateTextureFromSurface(renderer, surface10);
                dimencao(&rect10, surface10, 450, 20);
                atv7 = 1;
             }
                SDL_RenderCopy(renderer, logo10,  NULL, &rect10);                
            }

        if(ctlVic == 0 && ctlHit == 0 && ctlStand == 0){
           if(sum == 21){
             printf("veryfy blackjack\n");
             blackJackVerify(sum, sum2, &banco, &ctlVic);
           }
          }

        if(ctlVic == 0 && ctlHit >= 1 && ctlStand < 2){
          if(gambi2 != ctlHit){
            printf("veryfy Hit\n");
            hitVerify(sum, sum2, &banco, &ctlVic);
            gambi2 = ctlHit;
          }
         }

         if(ctlVic == 0 && (ctlStand >= 1 || gambiarra == 1)){ 
             printf("veryfy Stand\n");
             standVerify(sum, sum2, &banco, &ctlVic);   
         }

        if(ctlHit >= 3 && sum < 22 && ctlVic != -1){
            printf("Vitoria Charlie five\n");
            ctlVic = -1;
        }

         if(vitoryCtl == 1){
           printf("\nRESET\n");
           

           do {
             reinsere(&p1, baralho); 
            } while(!vazia(&p1));
                                      //reinserir cartas da pilha na lista
           do {
             reinsere(&p2, baralho);
            } while(!vazia(&p2));

            destroi(&p1);             // reinicializa pilhas e variaveis
            destroi(&p2);        

            sum = 0, sum2 = 0;        // zera somadores

            control_HIT = ctlVic = ctlHit = ctlStand = 0;  //zera variaveia de controle

            Gstate = 0;
            state = STATE_IN_GAME;
            gambiarra = trasBanco = trasClt = vitoryCtl = gambi2 = 0;
            atv1 = atv2 = atv3 = atv4 = atv5 = atv6 = atv7 = 0;

            game.ace2   = game.ace = game.stand = 0;
         }  

         if(banco != bancoCtl){
             sprintf(buffer2, "Cash %d$", banco);
             surfaceMessage =TTF_RenderText_Solid(Sans, buffer2, Black); 
             Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
             bancoCtl = banco;
         }
           if(sum != playCtl){
             sprintf(buffer3, "Player %d", sum);
             surfaceMessage2 =TTF_RenderText_Solid(Sans, buffer3, White); 
             Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);
             playCtl = sum;
         }
           if(trasBanco == 0){
             int aux = trasVar(var2);
             sprintf(buffer, "Dealer %d", aux);
             surfaceMessage3 =TTF_RenderText_Solid(Sans, buffer, White); 
             Message3 = SDL_CreateTextureFromSurface(renderer, surfaceMessage3);
          }
            if((sum2 != dealerCtl ) && trasBanco != 0){
             sprintf(buffer, "Dealer %d", sum2);
             surfaceMessage3 =TTF_RenderText_Solid(Sans, buffer, White); 
             Message3 = SDL_CreateTextureFromSurface(renderer, surfaceMessage3);
             dealerCtl = sum2;
         }
                SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
                SDL_RenderCopy(renderer, Message2, NULL, &Message_rect3);
                SDL_RenderCopy(renderer, Message3, NULL, &Message_rect2);
          }
         }    
        }

        SDL_RenderPresent(renderer);
    }

    // libera memoria alocada

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(iconeS);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(surface3);
    SDL_FreeSurface(surface4);
    SDL_FreeSurface(surface5);
    SDL_FreeSurface(surface6);
    SDL_FreeSurface(surface7);
    SDL_FreeSurface(surface8);
    SDL_FreeSurface(surface9);
    SDL_FreeSurface(surface10);


    SDL_FreeSurface(regras);
    SDL_FreeSurface(regrasB);
    SDL_FreeSurface(scores);

    SDL_DestroyTexture(scoresLogo);
    SDL_DestroyTexture(regrasLogoB);
    SDL_DestroyTexture(regrasLogo);

                              
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(logo2);
    SDL_DestroyTexture(logo3);
    SDL_DestroyTexture(logo4);
    SDL_DestroyTexture(logo5);
    SDL_DestroyTexture(logo6);
    SDL_DestroyTexture(logo7);
    SDL_DestroyTexture(logo8);
    SDL_DestroyTexture(logo9);
    SDL_DestroyTexture(logo10);
 
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage2);
    SDL_DestroyTexture(Message2);
    SDL_FreeSurface(surfaceMessage3);
    SDL_DestroyTexture(Message3);
    SDL_FreeSurface(surfaceMessage4);
    SDL_DestroyTexture(Message4);
    SDL_FreeSurface(surfaceMessage5);
    SDL_DestroyTexture(Message5);
    SDL_FreeSurface(surfaceMessage6);
    SDL_DestroyTexture(Message6);
    SDL_FreeSurface(surfaceMessage7);
    SDL_DestroyTexture(Message7);

    SDL_FreeSurface(titulo);
    SDL_DestroyTexture(tituloLogo);

    destruir(&baralho);
    destroi(&p1);          
    destroi(&p2);
    return 0;
}

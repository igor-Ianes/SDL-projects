#include <SDL2/SDL.h>
#include <stdio.h>


// Define FPS_CAP for capping fps to FPS
#define FPS_CAP
#ifndef FPS
#define FPS 60
#endif

#define FPS 60
#define BLOCKS 24

typedef struct bloco{
    SDL_Rect rect;
} bloco;

/* verify if colorfull block was hit*/
int hitVerify(bloco blocos[], SDL_Rect rect3, int *loopControl){
    int col = 0, cont = 0, i = 0, isAlive = 0;
      while(cont < BLOCKS)
      {
          if( blocos[i].rect.y + 20 < rect3.y){col = 0;}
          else if(blocos[i].rect.y > rect3.y + 50){col = 0;}
          else if(blocos[i].rect.x + 80 <  rect3.x){col = 0;}
          else if(blocos[i].rect.x > rect3.x + 50){col = 0;}
          else{col = 1;}

         if(col == 1){
          blocos[i].rect.x = -100; // block are sent out of screen
          blocos[i].rect.y = -100;
            return 1;
          }
          
         if(blocos[i].rect.x == -100){
            isAlive++;
         }

         if(isAlive == BLOCKS)
          *loopControl = 0;

        i++;
        cont++;
      }
    return -1;
}

/* verify if ball block was hit by skate, rect is skate rect3 is ball*/
int hit(SDL_Rect rect, SDL_Rect rect3){
    int col = 0;
     
          if(rect.y + 50 < rect3.y){col = 0;}
          else if(rect.y > rect3.y + 50){col = 0;}
          else if(rect.x + 150 <  rect3.x){col = 0;}
          else if(rect.x > rect3.x + 150){col = 0;}
          else{col = 1;}

         if(col == 1){
            return 1;
          }
    return -1;
}

/*
   skate stats
  rect3.x = 300;  
  rect3.y = 535;
  rect3.w = 150;
  rect3.h = 20;  // tried 50 for bigger hit range
  
     ball stats
  bloc.rect.h = 40;
  bloc.rect.w = 40;
  bloc.rect.x = 150;
  bloc.rect.y = 170;

*/

/* verify if ball block was hit*/
int outOfBounds(SDL_Rect rect){
    if(rect.y >= 530)
        return 1;
    return 0;
}

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window* window = SDL_CreateWindow(
      "Brick game",
      50, 30,
      800, 600,
      SDL_WINDOW_SHOWN
      );

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Rect rect2, rect3;
  SDL_Rect lado1, lado3, lado4;

  rect2.x = 500;
  rect2.y = 100;
  rect2.w = 50;
  rect2.h = 50;

  rect3.x = 300;  //25  inferior esq  - 25 superior esq - 700 dir - 700
  rect3.y = 535;  //535 inferior esq  - 25 superior esq -  25  dir - 535
  rect3.w = 150;  // era 50
  rect3.h = 20;   // era 50

  /* bordas da tela*/
  lado1.x = 10;
  lado1.y = 10;
  lado1.w = 10;
  lado1.h = 560;

  lado3.x = 10;
  lado3.y = 1;
  lado3.w = 780;
  lado3.h = 10;

  lado4.x = 780;
  lado4.y = 10;
  lado4.w = 10;
  lado4.h = 560;
  
  Uint32 start_time = SDL_GetTicks();
  printf("%d # \n", start_time);

  int start = 0;
  int control = 1;
  int var1 = 5, var2 = 5;
  

  /* square that acts like a ball */
  bloco bloc;
  bloc.rect.h = 40;
  bloc.rect.w = 40;
  bloc.rect.x = 150;
  bloc.rect.y = 170;

  const double freq_ms = SDL_GetPerformanceFrequency();
	Uint64 last_time = SDL_GetPerformanceCounter();

	unsigned int frame_counter = 0;
	double frame_timer = last_time;

  bloco blocos[BLOCKS];

   for (int i = 0, x = 40, y = 20; i < BLOCKS; i++, x += 90){
       if(x > 700){
        x = 40;
        y += 50;
       }
       blocos[i].rect.x = x;
       blocos[i].rect.y = y;
       blocos[i].rect.w = 80;
       blocos[i].rect.h = 20;
    }

  int hitFlag = 0;
  int loopControl = 1;

  while(loopControl){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if( event.type == SDL_QUIT ){
        exit(0);
      }
         else if(event.key.keysym.sym==SDLK_LEFT){
          rect2.x -= 20;
          start = 1;
            control = 1;
      }
        else if(event.key.keysym.sym==SDLK_RIGHT){
          rect2.x += 20;
          start = 1;
            control = 2;
      }
         else if(event.key.keysym.sym==SDLK_UP){
          rect2.y -= 20;
          start = 2;
            control = 1;
      }
          else if(event.key.keysym.sym==SDLK_DOWN){
          rect2.y += 20;
          start = 2;
            control = 2;
      }

    }
   

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect3); // square two
    SDL_RenderFillRect(renderer, &bloc.rect);


       /************** sides draw **************/
    SDL_RenderFillRect(renderer, &lado1); // square three
    SDL_RenderFillRect(renderer, &lado3); // square three
    SDL_RenderFillRect(renderer, &lado4); // square three

    
      /************** blocks draw **************/

     for (int i = 0; i < BLOCKS; i++){
      if(i < 8)
        SDL_SetRenderDrawColor(renderer, 200, 70, 200, 50);
      if (i > 7 && i < 16)
        SDL_SetRenderDrawColor(renderer, 250, 155, 155, 255);
      if(i > 15)
        SDL_SetRenderDrawColor(renderer, 10, 200, 110, 220);

       SDL_RenderFillRect(renderer, &blocos[i].rect);
    }

      /************** blocks draw **************/

    SDL_SetRenderDrawColor(renderer, 9, 20, 33, 255);
    SDL_RenderPresent(renderer);

    // verify hit between colorfull blocks and ball
    if(hitVerify(blocos, bloc.rect, &loopControl) == 1){
      var2 = -var2;
      var1 = -var1;
    }
    
    // verify hit between skate and ball
    if(hit(rect3, bloc.rect) == 1){
      var2 = -var2;
      var1 = var1; // if negative ball recochetes to same direction
      hitFlag = var2 - 10;
    }
     
    // verify if ball is out of bounds
    if(outOfBounds(bloc.rect) == 1)
      loopControl = 0;

    Uint64 current_time = SDL_GetPerformanceCounter();
		double delta = (current_time - last_time) / freq_ms * 1000.0;

		if (current_time > frame_timer + freq_ms){
      /* ********* 1 sec counter update ******** */
			printf("contador fps %d\n", frame_counter);
 //   printf("%d - %d\n", bloc.rect.x, bloc.rect.y);
			frame_counter = 0;
			frame_timer = current_time;     
      /* ********* 1 sec counter update ******** */
		}


  #ifdef FPS_CAP

   const double frame_delta = 1000.0 / FPS;

	 if (delta > frame_delta)
  #endif
		{
			/* ********** frame update ************** */
     
      /* controls skate moviment in x axis*/
      if(start == 1){
      if(rect3.x >= 700){control = 1;}
      if(rect3.x <= 25){control = 2;}

      if(control != 1){
        rect3.x += 5;
      }
      if(control != 2){
        rect3.x -= 5;
      }
    }
    
    /* controls skate moviment in y axis, if this 
    function is removed skate can stop with up command*/
    if(start == 2){
      if(rect3.y >= 535){control = 1;}
      if(rect3.y <= 25){control = 2;}

      if(control != 1){
        rect3.y += 5;
      }
      if(control != 2){
        rect3.y -= 5;
      }
    }   
        // updates moving block
        bloc.rect.y += hitFlag; // hitflag is a buffer that prevents
        hitFlag = 0;            // double hits in same frame
        bloc.rect.x += var1; 
        bloc.rect.y += var2;

        /*control colision on boards*/
        if(bloc.rect.x < 10){
          var1 = -var1; // left side
        }
        else if(bloc.rect.x + 50 > 750){
          var1 = -var1; // right side
        }
        else if(bloc.rect.y < 0){
          var2 = -var2; // upwards
        }
         else if(bloc.rect.y + 50 > 580){
          var2 = -var2;  // height
        }

      /* ********** frame update ************** */
		last_time = current_time;
			++frame_counter; 
		}
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}


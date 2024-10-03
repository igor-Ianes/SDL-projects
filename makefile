# MAKEFILE for folder's games compilation

#                  Blackjack graphic game config
blackJack=cards_games/blackjack/graphics/source/
blackHeaders=cards_games/blackjack/graphics/headerFiles
LINK1=-I$(blackHeaders) $(blackJack)main.c $(blackJack)lista.c $(blackJack)pilha.c $(blackJack)iteradores.c $(blackJack)cartas.c $(blackJack)graficos.c $(blackJack)pacote.c	$(blackJack)logica.c
OUTPUT1=BlackJack

#                  Bricks game compilation
LINK2=Bricks/spaceShip.c
OUTPUT2=sp

#                  Snake game compilation
LINK3=snake/cobra.c	snake/lista.c
OUTPUT3=snk3

#acess and linkage of SDL library
INCS2=-I.\game_development	-I.\game_library\SDL2\x86_64-w64-mingw32\include -I.\game_library\SDL2\x86_64-w64-mingw32\include\ -L.\game_library\SDL2\x86_64-w64-mingw32\lib
LIBSW2=-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

#Compilation options
CC=gcc
CFLAGS=-Wall -Wextra	-g -O2
OPTS1=-Wall -Wextra -pedantic
OPTS2=-Wall	-o


Blackjack:
	$(CC)	$(OPTS2)	$(OUTPUT1)	$(LINK1) $(INCS2) $(LIBSW2)

brick:
	$(CC)	$(OPTS2)	$(OUTPUT2)	$(LINK2) $(INCS2) $(LIBSW2)

snakeGame:
	$(CC)	$(OPTS2)	$(OUTPUT3)	$(LINK3) $(INCS2) $(LIBSW2)



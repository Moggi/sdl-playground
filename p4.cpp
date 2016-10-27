//  Biblioteas necessarias
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

//  Constantes e Variaveis              //Como no Bioshock infinite ;)


//  Prototipos de Funcoes


//  Classes/Estruturas Temporarias



/*
################            BODY            ################
*/


Game * g_game;

int main( int argc, char* argv[] )
{
    g_game = new Game();
    g_game->init("Chapter 1 - Here we go", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    while(g_game->running())
    {

        g_game->handleEvents();
        g_game->render();

    }
    g_game->clean();
    return 0;
}

/*
################            ####            ################
*/


//  Corpo das Funcoes


//

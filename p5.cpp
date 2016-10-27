//  Biblioteas necessarias
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "Player.h"

//  Constantes e Variaveis              //Como no Bioshock infinite ;)
Game * g_game;


//  Prototipos de Funcoes



//  Classes/Estruturas Temporarias



/*
################            BODY            ################
*/

int main( int argc, char* argv[] )
{

    g_game = new Game();
    bool g = g_game->init("Here we go again", SDL_WINDOWPOS_UNDEFINED,
    	SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(!g)
        return 0;
    Player * m_player = new Player;

    m_player->loadTexture("assets/thief_walk.gif", g_game->m_pRenderer );
    m_player->load( 0, 0, 90, 104, SDL_FLIP_NONE );

    g_game->addGameObject(m_player);
    int FPS = 30;
    Uint32 start;
    while( g_game->running() )
    {
        start = SDL_GetTicks();
        g_game->handleEvents();
        g_game->update();
        g_game->render();
        /*
        if( 1000/FPS > (SDL_GetTicks() - start) )
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - start) );
        */
    }

    g_game->clean();
    return 0;
}

/*
################            ####            ################
*/


//  Corpo das Funcoes




//

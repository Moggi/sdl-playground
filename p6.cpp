//  Biblioteas necessarias
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
    g_game->init("Here we go again", SDL_WINDOWPOS_UNDEFINED,
    	SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    Player * m_player = new Player;

    m_player->loadTexture("assets/animate_alpha.png", g_game->m_pRenderer );
    m_player->load( 0, 0, 128, 82, SDL_FLIP_NONE );

    g_game->addGameObject(m_player);

    while( g_game->running() )
    {

        g_game->handleEvents();
        g_game->render();
        g_game->update();

    }

    g_game->clean();
    return 0;
}

/*
################            ####            ################
*/


//  Corpo das Funcoes




//

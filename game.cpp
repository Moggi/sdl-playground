
#include <SDL2/SDL.h>
#include "Game.h"


Game::Game(){
	m_bRunning = false;
	m_state = -1;	//	-1 iniciando, 0 menu/pausado, 1 jogando
	m_event = new SDL_Event;
}


bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags){
	//
	if( !SDL_Init(SDL_INIT_EVERYTHING) )
    {
    	//	SDL iniciado
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if( m_pWindow )
		{
			//	Janela criada
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if( m_pRenderer )
				SDL_SetRenderDrawColor(m_pRenderer,50,50,50,255);
			else
				return false;	//	Nao foi possivel iniciar o Render do SDL
			m_state = 0;
		} else {
			return false;	//	Nao foi possivel abrir uma janela
		}
		//
	} else {
		return false;	//	Nao foi possivel iniciar o SDL
	}

	m_bRunning = true;
	return true;
}


void Game::addGameObject( GameObject * m_object ){
	m_gameObjects.push_back( m_object );
}


void Game::draw(){
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw( m_pRenderer );
	}
}


void Game::render( void ){
	//
	SDL_RenderClear(m_pRenderer);
	// loop through our objects and draw them
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
		m_gameObjects[i]->draw( m_pRenderer );
	//
	SDL_RenderPresent(m_pRenderer);
}


void Game::update( void ){
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}


void Game::handleEvents( void ){
	//
	if( SDL_PollEvent(m_event) )
	{
		switch (m_event->type)
		{
			case SDL_QUIT:
				m_bRunning = false;
				break;
			case SDL_KEYDOWN:{
				switch( m_event->key.keysym.sym )
				{
					case SDLK_RIGHT:
						for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
							m_gameObjects[i]->move(10);
						break;
					case SDLK_LEFT:
						for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
							m_gameObjects[i]->move(-10);
						break;
				}
				break;
			}
			default:
				break;
		}

	}
}


void Game::clean( void ){
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}




//


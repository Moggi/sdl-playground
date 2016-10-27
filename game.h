#ifndef __Game__
#define __Game__

#include "GameObject.h"
#include <vector>

class Game
{
public:
	SDL_Renderer * m_pRenderer;
	//
	Game();
	~Game();
	bool init(const char *, int, int, int, int, int);
	void addGameObject( GameObject * );
	void draw( void );
	void render( void );
	void update( void );
	void handleEvents( void );
	void clean( void );
	bool running( void ) { return m_bRunning; }

private:
	std::vector<GameObject *> m_gameObjects;
	SDL_Window * m_pWindow;
	SDL_Event * m_event;
	//TextureManager m_textureManager;

	int m_state;	//	-1 iniciando/finalizando, 0 menu/pausado, 1 jogando
	bool m_bRunning;
	int m_currentFrame;

};



#endif
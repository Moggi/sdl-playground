#ifndef __Player__
#define __Player__

#include "GameObject.h"


class Player : public GameObject
{
public:
	void load( int, int, int, int, SDL_RendererFlip );
	void draw( SDL_Renderer * );
	void update( void );
};


#endif
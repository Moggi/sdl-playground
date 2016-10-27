
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"


//

void Player::load( int x, int y, int width, int height, SDL_RendererFlip pflip ){
	GameObject::load(x, y, width, height, pflip);
}


void Player::draw( SDL_Renderer * pRenderer ){
	GameObject::draw( pRenderer );
}


void Player::update( void ){
    GameObject::update();
}





//

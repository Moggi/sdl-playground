
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameObject.h"

//

void GameObject::loadTexture( const char * fileName, SDL_Renderer * pRenderer ){
	SDL_Surface * pTempSurface = IMG_Load(fileName);
    m_pTexture = SDL_CreateTextureFromSurface( pRenderer, pTempSurface );
    SDL_FreeSurface( pTempSurface );
}

void GameObject::load( int x, int y, int width, int height, SDL_RendererFlip pflip ){
	srcRect.x = srcRect.y =0;
	srcRect.w = dstRect.w = width;
	srcRect.h = dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;
	flip = pflip;
}


void GameObject::draw( SDL_Renderer * pRenderer ){
	//
	SDL_RenderCopy(pRenderer, m_pTexture, &srcRect, &dstRect);
}


void GameObject::update( void ){
    srcRect.x = 90 * int(((SDL_GetTicks() / 100) % 6));
}

void GameObject::move( int x, int y ){
	if((x>0 && dstRect.x<0) || (x<0 && dstRect.x >0))
		flip = SDL_FLIP_HORIZONTAL;
	dstRect.x += x;
}

void GameObject::clean( void ){
	//
}

//

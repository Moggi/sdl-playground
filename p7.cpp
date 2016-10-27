#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>

SDL_Surface * screen;

class Object{
public:
	void loadTexture( int color, SDL_Renderer * render ){
		SDL_Surface * s1 = SDL_CreateRGBSurface(0, srcRect.w, srcRect.h, 32, 0, 0, 0, 0);
		SDL_FillRect(s1, NULL, color);
		m_pTexture = SDL_CreateTextureFromSurface(render,s1);
		SDL_FreeSurface(s1);
	}
	void load( int x, int y, int w, int h){
		dstRect.x = x;
		dstRect.y = y;
		srcRect.x = srcRect.y = 0;
		srcRect.w = dstRect.w = w;
		srcRect.h = dstRect.h = h;
	}
	void draw( SDL_Renderer * render ){
		SDL_RenderCopy(render, m_pTexture, &srcRect, &dstRect);
	}
	void update( int x, int y ){
		srcRect.x = x;
		srcRect.y = y;
	}
	bool colision( int x, int y, int w, int h ){
		if( sqrt( (srcRect.x - x)*(srcRect.x - x) + (srcRect.y - y)*(srcRect.y - y) ) < (h+srcRect.h))
			return true;
		if( sqrt( (srcRect.x - x)*(srcRect.x - x) + (srcRect.y - y)*(srcRect.y - y) ) < (w+srcRect.w))
			return true;
		return false;
	}
protected:
	SDL_Rect srcRect;	//	A imagem
	SDL_Rect dstRect;	//	Onde a imagem começa
	SDL_Texture * m_pTexture;
	//
};

class Snake : public Object {
public:
	Snake(){
		for(int i=0; i<5; i++){
			BodyX.push_back(dstRect.x + 15);
			BodyY.push_back(dstRect.y + 15);
		}
	}
	void updateBody( void ){
		for(std::vector<int>::size_type i = 0; i != BodyX.size(); i++){
			//SDL_FillRect(screen,&BodyX[i],0x0000FD00);
			//SDL_FillRect(screen,&BodyY[i],0x0000FD00);
		}
	}
	void draw( SDL_Renderer * render ){
		updateBody();
		Object::draw(render);
	}
	void direction( int i ){
		int speed = 2;
		if( i == 1 )
			dstRect.y -= speed;
		else if( i == 2 )
			dstRect.x += speed;
		else if( i == 3 )
			dstRect.y += speed;
		else if( i == 4 )
			dstRect.x -= speed;
	}
private:
	std::vector<int> BodyX;
	std::vector<int> BodyY;

};

int main(void)
{
	SDL_Window * window = NULL;
	SDL_Renderer * render = NULL;
	//
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("MODAFOKA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,  0);
	//screen = SDL_SetVideoMode(640, 480, 32,SDL_SWSURFACE);
	if( !window ){
		SDL_Quit();
		return 0;
	}
	render = SDL_CreateRenderer( window, -1, 0 );
	if( !render ){
		SDL_Quit();
		return 0;
	}
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	//
	Snake s1;
	s1.load(20,20,15,15);
	s1.loadTexture(0x0000FD00, render);

	//
	SDL_Event e;
	//
	bool run=true;
	while( run ){
		while(  SDL_PollEvent(&e) )
		{
			if(e.type == SDL_QUIT){
				run=false;
				break;
			}
			if(e.type == SDL_KEYDOWN || e.key.repeat != 0){
				switch( e.key.keysym.sym ){
					case SDLK_UP:
						s1.direction(1);
						break;
					case SDLK_RIGHT:
						s1.direction(2);
						break;
					case SDLK_DOWN:
						s1.direction(3);
						break;
					case SDLK_LEFT:
						s1.direction(4);
						break;
				}
			}
	}
		//
		SDL_RenderClear(render);
		s1.draw(render);
        SDL_RenderPresent(render);
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 1;
}

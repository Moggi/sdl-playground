#ifndef __GameObject__
#define __GameObject__


class GameObject
{
public:
	void loadTexture( const char *, SDL_Renderer * );
	void load( int, int, int, int, SDL_RendererFlip );
	void draw( SDL_Renderer * );
	void update( void );
	void move( int x=0, int y=0 );
	void clean( void );

protected:
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	SDL_Texture * m_pTexture;
	SDL_RendererFlip flip;
	/*
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	*/
	
};


#endif
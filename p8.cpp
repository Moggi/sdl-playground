
//

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//  Global variables
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//	Prototypes
void logSDLError(std::ostream &, const std::string &);
const char * DataPath(void);
SDL_Texture * renderText(const std::string &, const std::string &, SDL_Color, int, SDL_Renderer *);
void renderTexture(SDL_Texture *, SDL_Renderer *, int, int);
SDL_Texture * loadTexture(const std::string &, SDL_Renderer *);
void cleanUp(SDL_Renderer * renderer,SDL_Window * window);


//	Main
const std::string data_path = DataPath();

int main( int argc, char * argv[] )
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }
    if(TTF_Init() != 0){
        logSDLError(std::cout, "TTF_Init");
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    window = SDL_CreateWindow(
        "An SDL window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if( !window ){
        logSDLError(std::cout, "CreateWindow");
        cleanUp(renderer,window);
        return 1;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED //| SDL_RENDERER_PRESENTVSYNC
    );

    if( !renderer ){
        logSDLError(std::cout, "CreateRenderer");
        cleanUp(renderer,window);
        return 1;
    }

    //We'll render the string "TTF fonts are cool!" in white
    //Color is in RGBA format
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Texture * image = renderText(
        "Game Over",
        data_path + "assets/sample.ttf",
        color,
        64,
        renderer
    );

    if (image == NULL){
        // Clean up
        cleanUp(renderer,window);
        return 1;
    }
    //Get the texture w/h so we can center it in the screen
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    SDL_Event event;

    while( true )
    {

        if( SDL_PollEvent(&event) ){
            //
            if( event.type == SDL_QUIT ){
                break;
            }
            //
        }
        SDL_RenderClear(renderer);
        renderTexture(image, renderer, x, y);
        SDL_RenderPresent(renderer);

    }
    //
    // Clean up
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(image);
    cleanUp(renderer,window);
    return 0;
}




void logSDLError( std::ostream & os, const std::string & msg ){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

const char * DataPath( void ){
    std::string data_path;
    char * base_path = SDL_GetBasePath();
    if (base_path) {
        data_path = SDL_strdup(base_path);
        SDL_free(base_path);
    } else {
        data_path = SDL_strdup("./");
    }
    return data_path.c_str();
}


/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture * renderText( const std::string & message, const std::string & fontFile,
	SDL_Color color, int fontSize, SDL_Renderer * renderer )
{
    if(!TTF_WasInit() && TTF_Init()==-1) {
        logSDLError(std::cout, "TTF_Init");
        return NULL;
    }
	//Open the font
	TTF_Font * font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == NULL){
		logSDLError(std::cout, "TTF_OpenFont");
		return NULL;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface * surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == NULL){
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return NULL;
	}
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL){
		logSDLError(std::cout, "CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture( SDL_Texture * tex, SDL_Renderer * ren, int x, int y ){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}


/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture( const std::string & file, SDL_Renderer * ren ){
    SDL_Texture * texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == NULL)
        logSDLError(std::cout, "LoadTexture");
    return texture;
}

void cleanUp( SDL_Renderer * renderer,SDL_Window * window ){
    if(renderer)
        SDL_DestroyRenderer(renderer);
    if(window)
        SDL_DestroyWindow(window);
    if(TTF_WasInit())
        TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}



//

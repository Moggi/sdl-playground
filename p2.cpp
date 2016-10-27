//

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

//

void Init_openGL( void );
void Render( void );
bool Process_Events( void );

/*  ####################################################################  */

int main(int argc, char * argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window;

    window = SDL_CreateWindow(
        "Hue1 - SDL 2.0",					// window title
        SDL_WINDOWPOS_UNDEFINED,			// initial x position
        SDL_WINDOWPOS_UNDEFINED,			// initial y position
        800,								// width, in pixels
        600,								// height, in pixels
        SDL_WINDOW_OPENGL					// Flags
    );
  
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    Init_openGL();

    //	Here we go
    while( true )
    {
        //
    	Render();
        
        if( ! Process_Events() )
            break;

        SDL_GL_SwapWindow(window);
    } 

    //
    SDL_GL_DeleteContext(glcontext);  

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

/*  ####################################################################  */


//

void Init_openGL( void ){

    glClearColor( 100.0f, 100.0f, 100.0f, 1.0f);
    //
}

void Render( void ){

    glClear(GL_COLOR_BUFFER_BIT);
    //

}


bool Process_Events( void ){

    SDL_Event event;
        
    while( SDL_PollEvent(&event) )
    {
        //

        if( event.type == SDL_QUIT ){
            return false;
            break;
        }
        
        //
    }

    return true;
}



//
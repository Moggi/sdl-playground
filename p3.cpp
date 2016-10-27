//

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>


bool G_running;

//  PROTOTYPE

void Init_openGL( void );
void Render( void );


/*  ####################################################################  */

int main(int argc, char * argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window;

    window = SDL_CreateWindow(
        "Hue2 - SDL 2.0",					// window title
        SDL_WINDOWPOS_UNDEFINED,			// initial x position
        SDL_WINDOWPOS_UNDEFINED,			// initial y position
        800,								// width, in pixels
        600,								// height, in pixels
        SDL_WINDOW_OPENGL					// Flags
    );
  
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    Init_openGL();
    G_running = true;


    SDL_Event event;

    //	Here we go
    while( G_running )
    {
        //
    	Render();
    
        while( SDL_PollEvent(&event) )
        {
            //
            if( event.type == SDL_QUIT ){
                G_running = false;
                break;
            }
            if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ){
                G_running = false;
                break;
            }
            //
        }


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

    glShadeModel( GL_SMOOTH );
    glClearColor( 100.0f, 100.0f, 100.0f, 1.0f );
    //
}

void Render( void ){

    glClear(GL_COLOR_BUFFER_BIT);
    //
}



//
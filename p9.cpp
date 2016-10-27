//
//  main.cpp
//  SDLTutorial
//
//  Created by Ciaran McCormack on 25/09/13.
//  Copyright (c) 2013 Raiblin. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

using namespace std;

class Graphics
{
public:
    
    void update()
    {
        glClearColor(0.0f, 0.0f, rand() % 255 / 255.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
};

int EventFilter(void* userdata, SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            SDL_Log("Key Down %d", event->key.keysym.sym);
            return 0;
            
        case SDL_KEYUP:
            SDL_Log("Key Up %d", event->key.keysym.sym);
            return 0;
            
        case SDL_MOUSEMOTION:
            SDL_Log("Mouse Moved. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
            return 0;
            
        case SDL_MOUSEBUTTONDOWN:
            SDL_Log("Mouse Button Down %d", event->button.button);
            return 0;
            
        case SDL_MOUSEBUTTONUP:
            SDL_Log("Mouse Button Up %d", event->button.button);
            return 0;
            
        case SDL_MOUSEWHEEL:
            SDL_Log("Mouse Wheel");
            return 0;
    }
    
    return 1;
}

int main(int argc, const char * argv[])
{
    int width = 1080;
    int height = 720;
    
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
        return 0;
    }
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    //Create the window
    auto window = SDL_CreateWindow("SDL 2.0 OSX Tutorial", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    if (window == 0)
    {
        SDL_Quit();
        return false;
    }

    auto gl = SDL_GL_CreateContext(window);
    
    SDL_AddEventWatch(EventFilter, nullptr);
    
    unique_ptr<Graphics> graphics = unique_ptr<Graphics>(new Graphics());
    
    //Game Loop
    SDL_Event event;
    auto done = false;

    while( !done )
    {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                    
                case SDL_APP_TERMINATING:
                    SDL_Log("SDL_APP_TERMINATING");
                    break;
            }
        }
        graphics->update();
        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(gl);
    
    // Done! Close the window, clean-up and exit the program.
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


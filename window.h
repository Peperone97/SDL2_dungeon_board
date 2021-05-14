#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#endif
#ifdef  unix
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif
//#include "SDL2/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <exception>

#include "core.h"
//#include "new_core.h"
#include "texture.h"

#ifndef WINDOW
#define WINDOW

#define FPS 30
#define SECOND 1000
 

namespace Window{
    class Window{
    public:
        Window( const char *title, int width, int height );
        ~Window();
        void show();
        void run();
    private:
        int width, height, previous_x, previous_y; //previous x/y used for slide the map
        bool slide, draw, quit, ctrl_combination;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Event e;
        SDL_Thread *input_thread, *update_thread, *render_thread;

        Core *core;
        
        static void event_wrapper( void* obj ){
            static_cast<Window*>(obj)->eventManager();
        }
        static void render_wrapper( void* obj ){
            static_cast<Window*>(obj)->render();
        }
        static void update_wrapper( void *obj ){
            static_cast<Window*>(obj)->update();
        }
        void render();
        void update();
        void eventManager();
        void close();
        void prv();

    };
}

#endif

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <SDL2/SDL.h>

#ifndef WINDOW
#define WINDOW

namespace Window{
    class Window{
    public:
        Window( const char *title, int width, int height );
        ~Window();
        void show();
        void run();
    private:
        int width, height;
        SDL_Window *window;
        SDL_Renderer *renderer;

        void eventHandler();
        bool eventManager(SDL_Event e);
        void close();
    };
}

#endif
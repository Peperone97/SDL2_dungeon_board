#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core.h"
#include "texture.h"

#ifndef WINDOW
#define WINDOW

#define FPS 10
#define SECOND 1000
 

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
        SDL_Texture *texture;
        Core *core;

        void render();
        void update();
        bool eventManager(SDL_Event e);
        void close();
    };
}

#endif
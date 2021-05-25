#ifdef _WIN32
    #include "SDL2\include\SDL2\SDL.h"
    #include "SDL2\include\SDL2\SDL_image.h"
#endif
#ifdef unix
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif
//#include "SDL2/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <exception>

#include "baseWindow.h"
#include "core.h"
#include "texture.h"
#include "phrase.h"

#ifndef WINDOW
#define WINDOW
 

namespace Window{
    class Window : public BaseWindow{
    public:
        Window( const char *title, int width, int height, int numberOfTiles );
        ~Window();
    private:
        int previous_x, previous_y; //previous x/y used for slide the map
        bool slide, draw, ctrl_combination;

        SDL_Event e;

        Core *core;

        void render();
        void update();
        void eventManager();

    };
}

#endif

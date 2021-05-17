#ifdef _WIN32
    #include <SDL.h>
#endif
#ifdef unix
    #include <SDL2/SDL.h>
#endif
//#include "SDL2/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <math.h>

#include "phrase.h"
#include "baseWindow.h"

#ifndef INPUT_WINDOW
#define INPUT_WINDOW

namespace InputWindow{
    class InputWindow : public BaseWindow{
    public:
        InputWindow( const char* title, int width, int height );
        ~InputWindow();
        void run();

        int getGridDimension();
    private:
        int gridDimension;

        Phrase *dinamicText, *staticText;

        SDL_Thread *render_thread;

        static void render_wrapper(void* obj) {
            static_cast<InputWindow*>(obj)->render();
        }
        void render();
        
        void eventManager();
        void parseInput();

    };
}

#endif

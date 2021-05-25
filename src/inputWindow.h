#ifdef _WIN32
    #include "SDL2\include\SDL2\SDL.h"
#endif
#ifdef unix
    #include <SDL2/SDL.h>
#endif
//#include "SDL2/include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <math.h>

#include "baseWindow.h"
#include "phrase.h"
#include "button.h"
#include "dropdownMenu.h"
#include "cursor.h"

#ifndef INPUT_WINDOW
#define INPUT_WINDOW

namespace InputWindow{
    class InputWindow : public BaseWindow{
    public:
        InputWindow( const char* title, int width, int height );
        ~InputWindow();

        int getGridDimension();
    private:
        int gridDimension, charDimension;

        Phrase *dinamicText, *staticText;
        Button *button;
        DropdownMenu *menu;
        Cursor *cursor;

        void render();
        void update();
        
        void eventManager();
        void parseInput();

    };
}

#endif

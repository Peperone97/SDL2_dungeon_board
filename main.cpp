#ifdef _APPLE_

#include <stdio.h>
    
int main() {
    printf("Unknown error :(\n");
    return 1;
}

#else

#include <stdio.h>
#include <exception>

#include "window.h"
#include "inputWindow.h"
#include "errorWindow.h"

int main( int argc, char **argv ){
    int width = 800, height = 800;

    InputWindow::InputWindow* inputWindow;
    try {
        inputWindow = new InputWindow::InputWindow("Input", 369, 200);
    }
    catch (const char* c) {
        printf("%s\n", c);
        return 1;
    }
    inputWindow->show();
    inputWindow->run();
    int numberOfTiles = inputWindow->getGridDimension();
    delete inputWindow;

    if( numberOfTiles <= 32 || numberOfTiles > height ){
        ErrorWindow* err = new ErrorWindow("Error!", 300, 100);
        err->show();
        err->run();
        return 1;
    }

    Window::Window *win;
    try{
        win = new Window::Window( "Prove", width, height, numberOfTiles );
    }catch( const char *c ){
        printf("%s\n", c);
        return 1;
    }
    win->show();
    win->run();
    delete win;

    return 0;
}

#endif
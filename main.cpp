#ifdef _APPLE_

#inclde <stdio.h>
    
int main() {
    printf("Unknown error :(\n");
    return 1;
}

#else

#include <stdio.h>
#include <exception>
#include "window.h"

int main( int argc, char **argv ){

    Window::Window *win;
    try{
        win = new Window::Window( "Prove", 800, 800 );
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
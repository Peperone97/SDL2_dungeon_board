#include <stdio.h>
#include "window.hpp"

int main( int argc, char **argv ){

    Window::Window *win = new Window::Window( "Prove", 500, 500 );
    win->show();
    win->run();
    delete win;

    return 0;
}
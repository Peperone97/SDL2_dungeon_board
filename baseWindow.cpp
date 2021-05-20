#include "baseWindow.h"

BaseWindow::BaseWindow( const char* title, int width, int height ){
    this->width = width;
    this->height = height;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) { throw "Can't init SDL2"; }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_HIDDEN);
    if (window == NULL) { throw "Can't init SDL window"; }

    if (IMG_Init(IMG_INIT_PNG) < 0) { throw "Can't init png"; }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) { throw "Can't init SDL renderer"; }

    lock = SDL_CreateMutex();

}

void BaseWindow::show() {
    SDL_ShowWindow(window);
}

void BaseWindow::run() {
    quit = false;

    update_thread = SDL_CreateThread((SDL_ThreadFunction)BaseWindow::update_wrapper, "update", this);
    render_thread = SDL_CreateThread((SDL_ThreadFunction)BaseWindow::render_wrapper, "render", this);
    do {

        eventManager();

    } while (!quit);
}

void BaseWindow::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

BaseWindow::~BaseWindow(){
    close();
}
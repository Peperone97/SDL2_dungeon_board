#include "errorWindow.h"

ErrorWindow::ErrorWindow( const char* title, int width, int height ) : BaseWindow( title, width, height ){
    error = new Phrase( "ERROR!", 10, 10, width, height, 50, renderer );
}

void ErrorWindow::render() {
    do {
        SDL_LockMutex( lock );

        SDL_RenderClear(renderer);
        error->render( renderer );
        SDL_RenderPresent(renderer);

        SDL_UnlockMutex( lock );
        SDL_Delay(SECOND / FPS);
    } while (!quit);
}

void ErrorWindow::eventManager() {
    do {
        SDL_LockMutex( lock );
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else {
                //event text
                if (e.key.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                }
            }
        }
        SDL_UnlockMutex( lock );
        SDL_Delay(1); //milliseconds
    } while (!quit);
}

ErrorWindow::~ErrorWindow(){
	delete error;
}
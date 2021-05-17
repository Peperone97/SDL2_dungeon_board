#include "inputWindow.h"

InputWindow::InputWindow::InputWindow( const char* title, int width, int height ) : BaseWindow( title, width, height ){

    int charDimension = (width - width * 5 / 100 * 2) / 21;
    staticText = new Phrase("Insert grid dimension", width*5/100, height*10/100, width - width*5/100, height, charDimension, renderer);
    dinamicText = new Phrase("", width*30/100, height*30/100, width*40/100, height*40/100, charDimension, numbers_only, renderer);
    
}

void InputWindow::InputWindow::run() {
    quit = false;

    render_thread = SDL_CreateThread((SDL_ThreadFunction)InputWindow::render_wrapper, "render", this);

    do {

        eventManager();

    } while (!quit);
}

void InputWindow::InputWindow::render() {
    do {
        SDL_RenderClear(renderer);

        staticText->render(renderer);
        dinamicText->render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(SECOND / FPS);
    } while (!quit);
}

void InputWindow::InputWindow::eventManager() {
    do {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else {
                //event text
                if (e.key.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z' || e.key.keysym.sym >= '0' && e.key.keysym.sym <= '9') {
                        dinamicText->addCharacter(e.key.keysym.sym);
                    }
                    else if (e.key.keysym.sym == ' ') {
                        dinamicText->addCharacter(' ');
                    }
                    else if (e.key.keysym.sym == '.') {
                        dinamicText->addCharacter('.');
                    }
                    else if (e.key.keysym.sym == '-') {
                        dinamicText->addCharacter('-');
                    }
                    if (e.key.keysym.sym == SDLK_BACKSPACE) {
                        dinamicText->removeLastCharacter();
                    }
                    else if (e.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    else if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) {
                        parseInput();
                        quit = true;
                    }
                }
            }
        }
        SDL_Delay(1); //milliseconds
    } while (!quit);
}

void InputWindow::InputWindow::parseInput() {
    gridDimension = 0;
    char* input = dinamicText->getText();
    printf("%s\n", input);
    int dim = dinamicText->getPhraseLength();

    for( int i = 0; i < dim; i++ ){
        gridDimension += (input[i] - '0')* (int)pow((double)10, (double)dim - i - 1);
    }

}

int InputWindow::InputWindow::getGridDimension(){
    return gridDimension;
}

InputWindow::InputWindow::~InputWindow(){
    delete staticText;
    delete dinamicText;
}
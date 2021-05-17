#include "inputWindow.h"

InputWindow::InputWindow::InputWindow( const char* title, int width, int height ) : BaseWindow( title, width, height ){

    charDimension = (width - width * 5 / 100 * 2) / 21;
    staticText = new Phrase("Insert grid dimension", width*5/100, height*10/100, width - width*5/100, height, charDimension, renderer);
    dinamicText = new Phrase("", width/2, height*30/100, width*40/100, height*40/100, charDimension, numbers_only, renderer);

    button = new Button( "Confirm", width/2 - (width*40/100)/2 , height - height*20/100 * 2, width*40/100, height*20/100, renderer );
    
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
        SDL_RenderClear( renderer );

        staticText->render( renderer );
        dinamicText->setPosition( width/2 - dinamicText->getPhraseLength()/2 * charDimension, height * 30 / 100 ); // set the dinami text at center
        dinamicText->render( renderer );
        button->render( renderer );

        SDL_RenderPresent(renderer);

        SDL_Delay( SECOND / FPS );
    } while ( !quit );
}

void InputWindow::InputWindow::eventManager() {
    do {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else {
                if( e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT ){ //click on map
                    //printf("Click\n");
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    if( button->isClicked( x, y ) && dinamicText->getPhraseLength() > 0 ){
                        parseInput();
                        quit = true;
                    }
                }
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
                    else if ((e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) && dinamicText->getPhraseLength() > 0) {
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
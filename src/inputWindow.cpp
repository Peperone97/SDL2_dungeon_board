#include "inputWindow.h"

InputWindow::InputWindow::InputWindow( const char* title, int width, int height ) : BaseWindow( title, width, height ){

    charDimension = (width - width * 5 / 100 * 2) / 21;
    staticText = new Phrase("Insert grid dimension", width*5/100, height*10/100, width - width*5/100, height, charDimension, renderer);
    dinamicText = new Phrase("", width*60/100, height*33/100, width*40/100, height*40/100, charDimension, numbers_only, renderer);
    cursor = new Cursor( width*60/100, height*33/100, charDimension, renderer );

    button = new Button( "Confirm", width/2 - (width*40/100)/2 , height - height*20/100 * 2, width*40/100, height*20/100, renderer );

    menu = new DropdownMenu( 10, height*30/100, width*40/100, height*15/100, renderer );
    menu->addEntry( "Dungeon", renderer );
    menu->addEntry( "Home", renderer );
    menu->setText( "Dungeon" );
    
}

void InputWindow::InputWindow::render() {
    do {
        SDL_LockMutex( lock );

        SDL_RenderClear( renderer );

        staticText->render( renderer );
        dinamicText->render( renderer );
        cursor->render();
        
        if( !menu->isActivate() ){
            button->render(renderer);
        }
        menu->render( renderer );

        SDL_RenderPresent(renderer);

        SDL_UnlockMutex( lock );
        SDL_Delay( SECOND / FPS );
    } while ( !quit );
}

void InputWindow::InputWindow::update(){
    do {
        SDL_LockMutex( lock );

        cursor->update();
        cursor->updatePosition( width*60/100 + dinamicText->getPhraseLength() * charDimension, height*33/100 );

        SDL_UnlockMutex( lock );
        SDL_Delay(1); //milliseconds
    } while (!quit);
}

void InputWindow::InputWindow::eventManager() {
    do {
        SDL_LockMutex( lock );
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else {
                if( e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT ){// click
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    menu->handleEvent(x, y, CLICK);
                    if( button->isClicked( x, y ) && !menu->isActivate() && dinamicText->getPhraseLength() > 0  ){
                        parseInput();
                        quit = true;
                    }
                }
                if( e.type == SDL_MOUSEMOTION ){
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    button->isOnFocus( x, y );
                    menu->handleEvent( x, y, MOTION );
                }
                //event text
                if (e.key.type == SDL_KEYDOWN) {
                    if( dinamicText->getPhraseLength() <= 3 ){
                        if (e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z' || e.key.keysym.sym >= '0' && e.key.keysym.sym <= '9') {
                            dinamicText->addCharacter(e.key.keysym.sym);
                        }
                        if (e.key.keysym.scancode >= 89 && e.key.keysym.scancode <= 98) { //keypad
                            if (e.key.keysym.scancode == 98) {
                                dinamicText->addCharacter('0');
                            }
                            else { // 1 - 9
                                dinamicText->addCharacter(e.key.keysym.scancode-40); // char 1 = int 49
                            }
                        }
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
        SDL_UnlockMutex( lock );
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
    delete button;
    delete menu;
    delete cursor;
}
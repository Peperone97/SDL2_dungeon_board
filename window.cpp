#include "window.h"

Window::Window::Window(const char* title, int width, int height, int numberOfTiles ) : BaseWindow( title, width, height ){
    slide = false;
    ctrl_combination = false;

    core = new Core( height, height, height/numberOfTiles, renderer );

    dinamicText = new Phrase("", 4, 100, 200, 200, renderer);

}

void Window::Window::run(){
    quit = false;
    slide = false;
    draw = false;
    
    update_thread = SDL_CreateThread( (SDL_ThreadFunction)Window::update_wrapper, "update", this );
    render_thread = SDL_CreateThread((SDL_ThreadFunction)Window::render_wrapper, "render", this);
    do{

        eventManager();

    }while( !quit );
}

void Window::Window::render(){
    do {
        SDL_RenderClear(renderer);
        core->render();
        dinamicText->render( renderer );
        SDL_RenderPresent(renderer);

        SDL_Delay(SECOND / FPS);
    }while( !quit );
}

void Window::Window::update(){
    int new_x, new_y;
    do{
        if( slide ){
            SDL_GetMouseState( &new_x, &new_y );
            core->moveMap( new_x - previous_x, new_y - previous_y );
            previous_x = new_x;
            previous_y = new_y;
        }

        core->update();
        SDL_Delay( 1 ); //milliseconds
    }while( !quit );
}

void Window::Window::eventManager(){
    do{
        while( SDL_PollEvent( &e ) != 0){
            if( e.type == SDL_QUIT ){
                //printf("Quit\n");
                quit = true;
            }else{
                if( e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT ){ //click on map
                    //printf("Click\n");
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    core->handleEvent( x, y );
                    
                    draw = true;
                }
                if( e.type == SDL_MOUSEWHEEL ){ //zoom
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    if( e.wheel.y > 0){ //in
                        core->zoomIn( x, y );
                    }else{ //out
                        core->zoomOut( x, y );
                    }

                    draw = true;
                }
                if( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){ //start slide
                    SDL_GetMouseState( &previous_x, &previous_y );
                    slide = true;
                }
                if( e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT){ //stop slide
                    slide = false;
                }
                //create a new dungeon ctrl+n
                if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LCTRL ){
                    ctrl_combination = true;
                }
                if( e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LCTRL ){
                    ctrl_combination = false;
                }
                if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n ){
                    if( ctrl_combination ){
                        core->createNewDungeon();
                    }
                    draw = true;
                }
                //event text
                if(e.key.type == SDL_KEYDOWN){
                    if( !ctrl_combination ){
                        if ( e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z' || e.key.keysym.sym >= '0' && e.key.keysym.sym <= '9' ) {
                            dinamicText->addCharacter( e.key.keysym.sym );
                        }else if( e.key.keysym.sym == ' ' ){
                            dinamicText->addCharacter( ' ' );
                        }else if( e.key.keysym.sym == '.' ){
                            dinamicText->addCharacter( '.' );
                        }else if( e.key.keysym.sym == '-' ){
                            dinamicText->addCharacter( '-' );
                        }
                        if( e.key.keysym.sym == SDLK_BACKSPACE ){
                            dinamicText->removeLastCharacter();
                        }else if( e.key.keysym.sym == SDLK_ESCAPE ){
                            quit = true;
                        }
                    }
                    /*switch(e.key.keysym.sym){
                        case SDLK_w:
                            //update();
                            printf("W\n");
                        break;
                        case SDLK_a:
                            printf("A\n");
                        break;
                        case SDLK_s:
                            printf("S\n");
                        break;
                        case SDLK_d:
                            printf("D\n");
                        break;
                        case SDLK_UP:
                            printf("Up\n");
                            //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                        break;
                        case SDLK_DOWN:
                            printf("Down\n");
                            //SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
                        break;
                        case SDLK_LEFT:
                            printf("Left\n");
                            //SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        break;
                        case SDLK_RIGHT:
                            printf("Right\n");
                            //SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                        break;
                        case SDLK_SPACE:
                            printf("Space\n");
                            //SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                        break;
                        case SDLK_BACKSPACE:
                            printf("Remove\n");
                            dinamicText->removeLastCharacter();
                        break;
                        case SDLK_ESCAPE:
                            printf("Exit\n");
                            quit = true;
                    }*/
                }
            }
        }
        SDL_Delay( 1 ); //milliseconds
    }while( !quit );
}

Window::Window::~Window(){
    delete core;
}
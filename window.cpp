#include "window.h"

Window::Window::Window( const char *title, int width, int height ){
    this->width = width;
    this->height = height;
    slide = false;
    ctrl_combination = false;

    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){throw "Can't init SDL2";}  

    window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_HIDDEN );    
    if( window == NULL ){throw "Can't init SDL window";}

    if( IMG_Init( IMG_INIT_PNG ) < 0 ){throw "Can't init png";}

    renderer = SDL_CreateRenderer( window, -1, 0 );
    if( renderer == NULL ){throw "Can't init SDL renderer";}

    //SDL_SetRenderDrawColor( renderer, 120, 120, 120, 255 );

    //initialMenu = new Menu( 0, 0, 0, 0, "prv");

    core = new Core( width, height, height/40, renderer );

}

void Window::Window::show(){
    SDL_ShowWindow( window );
}

void Window::Window::run(){
    quit = false;
    slide = false;
    draw = false;
    input_thread = SDL_CreateThread( (SDL_ThreadFunction)Window::event_wrapper, "input", this );
    update_thread = SDL_CreateThread( (SDL_ThreadFunction)Window::update_wrapper, "update", this );
    do{

        render();
        SDL_Delay( SECOND / FPS );

    }while( !quit );
}

void Window::Window::render(){
    //if( draw ){ //render only if is an update
    SDL_RenderClear( renderer );
    core->render();
    //}
    SDL_RenderPresent( renderer );
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
        SDL_Delay( 100 ); //milliseconds
    }while( !quit );
}

void Window::Window::close(){
    delete core;
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void Window::Window::eventManager(){
    do{
        while( SDL_PollEvent( &e ) != 0){
            if( e.type == SDL_QUIT ){
                quit = true;
            }else{
                if( e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT ){ //click on map
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
                    core->createNewDungeon();
                    draw = true;
                }

                if(e.key.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
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
                        case SDLK_ESCAPE:
                            printf("Exit\n");
                            quit = true;
                    }
                }
            }
        }
        SDL_Delay( 100 ); //milliseconds
    }while( !quit );
}

Window::Window::~Window(){
    close();
}
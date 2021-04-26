#include "window.h"

Window::Window::Window( const char *title, int width, int height ){
    this->width = width;
    this->height = height;

    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){throw "Can't init SDL2";}  

    window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_HIDDEN );    
    if( window == NULL ){throw "Can't init SDL window";}

    if( IMG_Init( IMG_INIT_PNG ) < 0 ){throw "Can't init png";}

    renderer = SDL_CreateRenderer( window, -1, 0 );
    if( renderer == NULL ){throw "Can't init SDL renderer";}

    floor = new Floor( width, height, renderer );

    //SDL_Surface *surf = SDL_LoadBMP( "bmp/H30_heavyarmor.bmp" );
    /*SDL_Surface *surf = IMG_Load( "img/floor.png" );
    if( surf == 0 ){throw IMG_GetError();}
    texture = SDL_CreateTextureFromSurface( renderer, surf );NULL
    if( texture == 0 ){throw "Creating texture error";}
    SDL_FreeSurface( surf );

    source = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    destination = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    
    SDL_QueryTexture( texture, NULL, NULL, &source->w, &source->h );
    
    destination->x = 0;
    destination->y = 0;

    //source->x = 33;
    source->x = 161;
    source->y = 41;
    source->w = 38;
    source->h = 38;

    destination->w = 200;
    destination->h = 200;*/

}

void Window::Window::show(){
    SDL_ShowWindow( window );
}

void Window::Window::run(){
    bool quit = false;
    SDL_Event e;
    do{
        while( SDL_PollEvent( &e ) != 0){
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            else{
                quit = eventManager(e);
            }
        }

        render();

    }while( !quit );
}

void Window::Window::render(){
    SDL_RenderClear( renderer );
    floor->render( 0, 50 );
    //SDL_RenderCopy( renderer, texture, source, destination );
    SDL_RenderPresent( renderer );
}

void Window::Window::close(){
    delete floor;
    free( source );
    free( destination);
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

bool Window::Window::eventManager(SDL_Event e){
    if(e.key.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_w:
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
                return true;
        }
    }
    return false;
}

Window::Window::~Window(){
    close();
}
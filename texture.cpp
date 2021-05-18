#include "texture.h"

Texture::Texture( const char *path, SDL_Renderer *renderer ){
    
    SDL_Surface *surf = IMG_Load( path );
    if( surf == 0 ){throw IMG_GetError();}

    texture = SDL_CreateTextureFromSurface( renderer, surf );
    if( texture == 0 ){throw "Creating texture error";}

    SDL_FreeSurface( surf );

}

void Texture::render( SDL_Renderer *renderer, SDL_Rect *clip, SDL_Rect *destination ){

    SDL_RenderCopy( renderer, texture, clip, destination );
}

void Texture::changeColor(uint8_t r, uint8_t g, uint8_t b){
    SDL_SetTextureColorMod( texture, r, g, b );
}

Texture::~Texture(){
    SDL_DestroyTexture( texture );
}
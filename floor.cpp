#include "floor.h"

Floor::Floor( int width, int height, SDL_Renderer *renderer ){
    this->width = width;
    this->height = height;
    this->renderer = renderer;
    destination = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    for( int i = 0; i < 4; i++ ){
        tiles[i] = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    }
    //first tile
    tiles[0]->x = 161;
    tiles[0]->y = 1;
    tiles[0]->w = 38;
    tiles[0]->h = 38;
    //second tile
    tiles[1]->x = 201;
    tiles[1]->y = 1;
    tiles[1]->w = 38;
    tiles[1]->h = 38;
    //third tile
    tiles[2]->x = 241;
    tiles[2]->y = 1;
    tiles[2]->w = 38;
    tiles[2]->h = 38;
    //fourth tile
    tiles[3]->x = 161;
    tiles[3]->y = 41;
    tiles[3]->w = 38;
    tiles[3]->h = 38;

    texture = new Texture( "img/floor.png", renderer );
}

void Floor::render( int nOfTiless, int dimensionOfTiles ){
    destination->w = dimensionOfTiles;
    destination->h = dimensionOfTiles;
    for( int i = 0; i < width; i += dimensionOfTiles ){
        destination->x = i;
        for( int j = 0; j < height; j += dimensionOfTiles ){
            destination->y = j;
            texture->render( renderer, tiles[1], destination );
        }
    }
}

Floor::~Floor(){
    for( int i = 0; i < 4; i++ ){
        free(tiles[i]);
    }
    free(destination);
    delete texture;
}
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "texture.h"
#include "entity.h"

#ifndef FLOOR
#define FLOOR

class Core{
public:
    Core( int width, int height, int tileDimesion, SDL_Renderer *renderer );
    ~Core();
    void render();
    void update();
    void handleEvent( int x, int y );
    void zoomIn( int x, int y );
    void zoomOut( int x, int y );
private:
    int width, height, tileDimesion, zoomLevel;
    Entity ***entities;
    SDL_Rect **destination;
    SDL_Renderer *renderer;
    SDL_Rect *tiles[4];
    Texture *texture;

    void repositioning( int newDim, int pos_i, int pos_j );
    int* pointOfClick( int x, int y );
};

#endif
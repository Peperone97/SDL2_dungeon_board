#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "texture.h"

#ifndef FLOOR
#define FLOOR

class Floor{
public:
    Floor( int width, int height, SDL_Renderer *renderer );
    ~Floor();
    void render( int nOfTiles, int dimensionOfTiles );
private:
    int width, height;
    SDL_Rect *destination;
    SDL_Renderer *renderer;
    SDL_Rect *tiles[4];
    Texture *texture;
};

#endif
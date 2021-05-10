#include <stdio.h>
#include <SDL2/SDL.h>
//#include "SDL2/include/SDL.h"
#include <stdlib.h>
#include <time.h>
#include "texture.h"
#include "entity.h"
#include "map.h"

#ifndef CORE
#define CORE

class Core{
public:
    Core( int width, int height, int tileDimesion, SDL_Renderer *renderer );
    ~Core();
    void render();
    void update();
    void handleEvent( int x, int y );
    void zoomIn( int x, int y );
    void zoomOut( int x, int y );
    void moveMap( int x_move, int y_move );
    void createNewDungeon();
private:
    int width, height, tileDimesion, zoomLevel;
    int dim_i, dim_j; //dimension of matrix
    int **typeOfTile, **map;
    Entity ***entities;
    SDL_Rect **destination; //the matrix of floor tiles
    SDL_Renderer *renderer;
    SDL_Rect *tiles[4];
    Texture *texture;
    //render cordinates
    int render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y;
    
    void repositioning( int newDim, int pos_i, int pos_j );
    int* pointOfClick( int x, int y );
    void updateVisiblesIndex();
    bool isOnTopOfTheScreen( int i, int j );
    bool isOnBottomOfTheScreen( int i, int j );
};

#endif
#ifdef _WIN32
    #include <SDL.h>
#endif
#ifdef unix
    #include <SDL2/SDL.h>
#endif
//#include "SDL2/include/SDL.h"

#include <cmath>

#include "texture.h"
#include "timer.h"

#ifndef ENTITY
#define ENTITY

class Entity{
public:
    Entity( const char* path, SDL_Renderer *renderer );
    ~Entity();
    void addEntity( int dimension, int x, int y );
    virtual void render(){};
    virtual void update(){};
    void updateDimension( int newDimension );
    void updatePosition( int new_x, int new_y );
protected:
    SDL_Renderer *renderer;
    SDL_Rect position, *tile;
    Texture *texture;
    Timer *timer;
};

#endif
#include <SDL2/SDL.h>
#include "texture.h"

#ifndef ENTITY
#define ENTITY

class Entity{
public:
    Entity( const char* path, SDL_Renderer *renderer );
    ~Entity();
    void addEntity( int dimension, int x, int y );
    void render();
    void update();
private:
    int sprite;
    SDL_Renderer *renderer;
    SDL_Rect *entity[2];
    SDL_Rect *position;
    Texture *texture;
};

#endif
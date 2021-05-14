#include "entity.h"

Entity::Entity( const char* path, SDL_Renderer *renderer ){
    sprite = 0;
    this->renderer = renderer;
    texture = new Texture( path, renderer );
    timer = new Timer();

    position = (SDL_Rect*)malloc( sizeof(SDL_Rect) );

    entity[0] = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    entity[1] = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    //
    entity[0]->x = 0;
    entity[0]->y = 39;
    entity[0]->w = 49;
    entity[0]->h = 46;
    //
    entity[1]->x = 49;
    entity[1]->y = 39;
    entity[1]->w = 43;
    entity[1]->h = 46;
    
}

void Entity::addEntity( int dimension, int x, int y ){
    position->x = x;
    position->y = y;
    position->w = dimension;
    position->h = dimension;
}

void Entity::render(){
    texture->render( renderer, entity[sprite], position );
}

void Entity::update(){
    timer->start();
    //printf("%f\t%f\n", timer->getPassedTime(), fmod(timer->getPassedTime(), 200));
    int sec = fmod(timer->getPassedTime(), 100);
    if( sec >= 0 && sec <= 1 ){
        if( sprite == 0 ){
            sprite = 1;
        }else{
            sprite = 0;
        }
    }
}

void Entity::updateDimension( int newDimension ){
    position->w = newDimension;
    position->h = newDimension;
}

void Entity::updatePosition( int new_x, int new_y ){
    position->x = new_x;
    position->y = new_y;
}

Entity::~Entity(){
    free(entity[0]);
    free(entity[1]);
    delete texture;
}
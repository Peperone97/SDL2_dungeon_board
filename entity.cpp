#include "entity.h"

Entity::Entity( const char* path, SDL_Renderer *renderer ){
    this->renderer = renderer;
    texture = new Texture( path, renderer );
    timer = new Timer();
}

void Entity::addEntity( int dimension, int x, int y ){
    position.x = x;
    position.y = y;
    position.w = dimension;
    position.h = dimension;
}

void Entity::updateDimension( int newDimension ){
    position.w = newDimension;
    position.h = newDimension;
}

void Entity::updatePosition( int new_x, int new_y ){
    position.x = new_x;
    position.y = new_y;
}

Entity::~Entity(){
    delete texture;
    delete timer;
}
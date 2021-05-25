#include "movementArrow.h"

MovementArrow::MovementArrow(int x, int y, int dim, enum Direction orientation, SDL_Renderer* renderer) : Entity("img/sprites.png", renderer){
	texture->changeColor( 255, 0, 0 );

	tile = (SDL_Rect*)malloc( sizeof(SDL_Rect) );

	tile->x = 0;
	tile->y = 138;
	tile->w = 21;
	tile->h = 48;

	position.x = x;
	position.y = y;
	position.w = dim;
	position.h = dim;

	switch( orientation ){
		case DOWN:
			texture->rotate(180);
		break;
		case LEFT:
			texture->rotate(90);
		break;
		case RIGHT:
			texture->rotate(270);
		break;

	}
	
}

void MovementArrow::render() {
	texture->render(renderer, tile, &position);
}

MovementArrow::~MovementArrow(){
	free(tile);
}
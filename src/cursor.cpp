#include "cursor.h"

Cursor::Cursor(int x, int y, int dim, SDL_Renderer* renderer) : Entity( "img/sprites.png", renderer ){
	tile = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
	
	tile->x = 127;
	tile->y = 102;
	tile->w = 6;
	tile->h = 7;

	position.x = x;
	position.y = y;
	position.w = dim;
	position.h = dim;

	is_visible = true;
}

void Cursor::update(){
	timer->start();
	int sec = fmod(timer->getPassedTime(), 800);
	if( sec >= 0 && sec <= 1 ){
		is_visible = !is_visible;
	}
}

void Cursor::render(){
	if( is_visible ){
		texture->render( renderer, tile, &position );
	}
}

Cursor::~Cursor(){
	free( tile );
}
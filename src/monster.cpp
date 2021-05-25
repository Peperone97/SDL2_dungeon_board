#include "monster.h"

Monster::Monster(int x, int y, int dim, SDL_Renderer* renderer) : Entity("img/sprites.png", renderer) {
	tile = (SDL_Rect*)malloc( sizeof(SDL_Rect) * 2 );

	tile[0].x = 0;
	tile[0].y = 39;
	tile[0].w = 49;
	tile[0].h = 46;
	//
	tile[1].x = 49;
	tile[1].y = 39;
	tile[1].w = 43;
	tile[1].h = 46;

	position.x = x;
	position.y = y;
	position.w = dim;
	position.h = dim;

	sprite = 0;
}

void Monster::update() {
	timer->start();
	int sec = fmod(timer->getPassedTime(), 100);
	if (sec >= 0 && sec <= 1) {
		if( sprite ){ sprite = 0; }
		else{ sprite = 1; }
	}
}

void Monster::render(){
	texture->render(renderer, &tile[sprite], &position);
}

Monster::~Monster(){
	free( tile );
}
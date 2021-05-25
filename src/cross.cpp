#include "cross.h"

Cross::Cross(int x, int y, int dim, SDL_Renderer* renderer) : Entity("img/sprites.png", renderer) {
	texture->changeColor(255, 0, 0);

	tile = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	tile->x = 153;
	tile->y = 0;
	tile->w = 38;
	tile->h = 38;

	position.x = x;
	position.y = y;
	position.w = dim;
	position.h = dim;

}

void Cross::render() {
	texture->render(renderer, tile, &position);
}

Cross::~Cross() {
	free(tile);
}
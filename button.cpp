#include "button.h"

Button::Button( const char* text, int x, int y, int width, int height, SDL_Renderer *renderer ) {
	texture = new Texture("img/sprites.png", renderer);

	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;

	tile.x = 0;
	tile.y = 110;
	tile.w = 25;
	tile.h = 12;

	int l = stringLen( text );
	int dim_x = width + x, dim_y = height + y;

	this->text = new Phrase( text, x+width/2 - (height*30/100*l+l)/2, y+height/2 - (height*30/100)/2, dim_x, dim_y, height*30/100, renderer );
}

bool Button::isClicked( int x, int y ){
	if( x >= position.x && x <= position.x + position.w ){
		if( y >= position.y && y <= position.y + position.h ){
			return true;
		}
		return false;
	}
	return false;
}

void Button::render( SDL_Renderer *renderer ){
	texture->render( renderer, &tile, &position );
	text->render( renderer );
}

int Button::stringLen( const char *s ){
	int i = 0;
	while (s[i] != '\0') { i++; }
	return i;
}

Button::~Button(){
	delete texture;
	delete text;
}
#include "button.h"

Button::Button( const char* text, int x, int y, int width, int height, SDL_Renderer *renderer ) {
	texture = new Texture("img/sprites.png", renderer);
	focused = false;

	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;

	tile.x = 0;
	tile.y = 110;
	tile.w = 25;
	tile.h = 12;

	background_position.x = x;
	background_position.y = y;
	background_position.w = width;
	background_position.h = height;

	background_tile.x = 25;
	background_tile.y = 110;
	background_tile.w = 25;
	background_tile.h = 12;

	int l = stringLen( text );
	int dim_x = width + x, dim_y = height + y;

	this->text = new Phrase( text, x+width/2 - (height*30/100*l+l)/2, y+height/2 - (height*30/100)/2, dim_x, dim_y, height*30/100, renderer );
}

bool Button::isClicked( int x, int y ){
	printf("x: %d, y: %d\n", position.x, position.y);
	printf("X: %d <= %d <= %d\n", position.x, x, position.x + position.w);
	printf("Y: %d <= %d <= %d\n", position.y, y, position.y + position.h);
	if (x >= position.x && x <= position.x + position.w) {
		printf("X ok\n");
		if (y >= position.y && y <= position.y + position.h) {
			printf("Y ok\n");
			return true;
		}
		printf("\n");
		return false;
	}
	printf("\n");
	return false;
}

void Button::isOnFocus(int x, int y){
	if (x >= position.x && x <= position.x + position.w) {
		if (y >= position.y && y <= position.y + position.h) {
			focused = true;
		}else{
			focused = false;
		}
	}else{
		focused = false;
	}
}

void Button::render( SDL_Renderer *renderer ){
	texture->render(renderer, &tile, &position);
	if( focused ){
		texture->render(renderer, &background_tile, &background_position);
		text->changeColor( 0,0,0 );
	}else{
		text->changeColor(255, 255, 255);
	}
	text->render( renderer );
}

char *Button::getText(){
	return text->getText();
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
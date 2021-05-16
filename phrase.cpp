#include "phrase.h"

Phrase::Phrase( const char* phrase, int x, int y, int width, int height, SDL_Renderer *renderer ) {
	texture = new Texture( "img/sprites.png", renderer );

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	phraseLenght = 0;

	while (phrase[phraseLenght] != '\0') { phraseLenght++; }

	posithions = (SDL_Rect*)malloc( sizeof(SDL_Rect) * (phraseLenght) );
	tiles = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLenght));

	for (int i = 0; i < phraseLenght; i++ ) {
		fromCharToImage( upperCase(phrase[i]), i );
	}
	if( phraseLenght > 0 ){
		posithioningChar();
	}

}

void Phrase::fromCharToImage(char c, int positionIndex) {
	if ( c == ' ' ) {
		tiles[positionIndex].x = 0;
		tiles[positionIndex].y = 0;
		tiles[positionIndex].w = 0;
		tiles[positionIndex].h = 0;
	}else if( c == '-' ){
		tiles[positionIndex].x = 88;
		tiles[positionIndex].y = 105;
		tiles[positionIndex].w = IMAGE_CHAR_WIDTH_DIMENSION;
		tiles[positionIndex].h = 4;
	}else if( c == '.' ){
		tiles[positionIndex].x = 112;
		tiles[positionIndex].y = 102;
		tiles[positionIndex].w = IMAGE_CHAR_WIDTH_DIMENSION;
		tiles[positionIndex].h = IMAGE_CHAR_HEIGHT_DIMENSION;
	}else if (c >= '0' && c <= '9') {
		if ( c == '0' ) {
			tiles[positionIndex].x = 72;
			tiles[positionIndex].y = NUMBER_Y_POSITION;
			tiles[positionIndex].w = IMAGE_CHAR_WIDTH_DIMENSION;
			tiles[positionIndex].h = IMAGE_CHAR_HEIGHT_DIMENSION;
		}
		else {
			tiles[positionIndex].x = (IMAGE_CHAR_WIDTH_DIMENSION * (c - '1')) + (1 * (c - '1'));
			tiles[positionIndex].y = NUMBER_Y_POSITION;
			tiles[positionIndex].w = IMAGE_CHAR_WIDTH_DIMENSION;
			tiles[positionIndex].h = IMAGE_CHAR_HEIGHT_DIMENSION;
		}
	}
	else if( c <= LAST_FIRST_ROW_CAHR ){ // A - P
		tiles[positionIndex].x = (IMAGE_CHAR_WIDTH_DIMENSION * (c - 'A')) + (1 * (c - 'A'));
		tiles[positionIndex].y = FIRST_ROW_Y_POSITION;
		tiles[positionIndex].w = IMAGE_CHAR_WIDTH_DIMENSION;
		tiles[positionIndex].h = IMAGE_CHAR_HEIGHT_DIMENSION;
	}else{ // Q - Z
		tiles[positionIndex].x = IMAGE_CHAR_WIDTH_DIMENSION * (c - 'Q') + 1 * (c - 'Q');
		tiles[positionIndex].y = SECOND_ROW_Y_POSITION;
		tiles[positionIndex].w = IMAGE_CHAR_WIDTH_DIMENSION;
		tiles[positionIndex].h = IMAGE_CHAR_HEIGHT_DIMENSION;
	}
}

void Phrase::posithioningChar() {
	
	int charWidthDimension = width / phraseLenght;
	int charHeightDimension = height / phraseLenght;
	int charDimension = 0;
	if( charWidthDimension < charHeightDimension ){
		charDimension = charWidthDimension;
	}else{
		charDimension = charHeightDimension;
	}

	int posX = x;
	int posY = y;

	for (int i = 0; i < phraseLenght; i++) {
		posithions[i].x = posX;
		posithions[i].y = posY;
		posithions[i].w = charDimension;
		posithions[i].h = charDimension;

		(posX += charDimension)++;
		//(posY += y)++;
	}

}

void Phrase::addCharacter( const char c ){
	phraseLenght++;
	
	tiles = (SDL_Rect*)realloc( tiles, (sizeof(SDL_Rect) * phraseLenght) );
	posithions = (SDL_Rect*)realloc( posithions, (sizeof(SDL_Rect) * phraseLenght) );

	fromCharToImage( upperCase( c ), phraseLenght-1 );
	posithioningChar();
}

void Phrase::removeLastCharacter(){
	if( phraseLenght > 0 ){
		phraseLenght--;

		SDL_Rect *new_posithions = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLenght));
		SDL_Rect *new_tiles = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLenght));

		for (int i = 0; i < phraseLenght; i++ ) {
			new_posithions[i].x = posithions[i].x;
			new_posithions[i].y = posithions[i].y;
			new_posithions[i].w = posithions[i].w;
			new_posithions[i].h = posithions[i].h;
			new_tiles[i].x = tiles[i].x;
			new_tiles[i].y = tiles[i].y;
			new_tiles[i].w = tiles[i].w;
			new_tiles[i].h = tiles[i].h;
		}

		free(tiles);
		free(posithions);

		posithions = new_posithions;
		tiles = new_tiles;

		if( phraseLenght > 0 ){
			posithioningChar();
		}
	}
}

void Phrase::render( SDL_Renderer* renderer ) {
	for (int i = 0; i < phraseLenght; i++) {
		texture->render( renderer, &tiles[i], &posithions[i] );
	}
}

char Phrase::upperCase( char c ){
	if ('a' <= c && c <= 'z') {
		return c - 32;
	}
	return c;
}
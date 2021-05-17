#include "phrase.h"

Phrase::Phrase( const char* phrase, int x, int y, int width, int height, SDL_Renderer *renderer ) {
	
	dinamicTextDimension = true;
	selection = all;

	commonInitialization( phrase, x, y, width, height, renderer );

}

Phrase::Phrase( const char* phrase, int x, int y, int width, int height, int charDimension, SDL_Renderer* renderer ){
	
	dinamicTextDimension = false;
	this->charDimension = charDimension;
	selection = all;
	
	commonInitialization(phrase, x, y, width, height, renderer);
}
Phrase::Phrase( const char* phrase, int x, int y, int width, int height, enum INPUT_TYPE selection, SDL_Renderer* renderer ){

	dinamicTextDimension = true;
	this->selection = selection;

	commonInitialization(phrase, x, y, width, height, renderer);
}
Phrase::Phrase( const char* phrase, int x, int y, int width, int height, int charDimension, enum INPUT_TYPE selection, SDL_Renderer* renderer ){

	dinamicTextDimension = false;
	this->charDimension = charDimension;
	this->selection = selection;

	commonInitialization(phrase, x, y, width, height, renderer);
}

void Phrase::commonInitialization( const char* phrase, int x, int y, int width, int height, SDL_Renderer* renderer ){

	texture = new Texture("img/sprites.png", renderer);

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	phraseLength = 0;

	while (phrase[phraseLength] != '\0') { phraseLength++; }
	this->phrase = (char*)malloc( sizeof( char ) * (phraseLength+1));
	this->phrase[phraseLength] = '\0';

	posithions = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLength));
	tiles = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLength));

	for (int i = 0; i < phraseLength; i++) {
		this->phrase[i] = phrase[i];
		fromCharToImage(upperCase(phrase[i]), i);
	}
	if (phraseLength > 0) {
		posithioningChar();
	}

}

void Phrase::setPosition( int x, int y ){
	this->x = x;
	this->y = y;
	posithioningChar();
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
	
	if( dinamicTextDimension ){
		int charWidthDimension = width / phraseLength;
		int charHeightDimension = height / phraseLength;
		if (charWidthDimension < charHeightDimension) {
			charDimension = charWidthDimension;
		}
		else {
			charDimension = charHeightDimension;
		}
	}

	int posX = x;
	int posY = y;

	for (int i = 0; i < phraseLength; i++) {
		posithions[i].x = posX;
		posithions[i].y = posY;
		posithions[i].w = charDimension;
		posithions[i].h = charDimension;

		(posX += charDimension)++;
		//(posY += y)++;
	}

}

void Phrase::addCharacter( const char c ){
	if( isAdmitted( upperCase(c) ) ){
		phraseLength++;
		char *newPhrase = (char*)malloc( sizeof( char ) * (phraseLength+1));
		newPhrase[phraseLength] = '\0';
		for( int i = 0; i < phraseLength - 1; i++ ){
			newPhrase[i] = phrase[i];
		}
		newPhrase[phraseLength - 1] = c;
		free(phrase);
		phrase = newPhrase;
	
		tiles = (SDL_Rect*)realloc( tiles, (sizeof(SDL_Rect) * phraseLength) );
		posithions = (SDL_Rect*)realloc( posithions, (sizeof(SDL_Rect) * phraseLength) );

		fromCharToImage( upperCase( c ), phraseLength-1 );
		posithioningChar();
	}
}

void Phrase::removeLastCharacter(){
	if( phraseLength > 0 ){
		phraseLength--;
		phrase[phraseLength] = '\0';

		SDL_Rect *new_posithions = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLength));
		SDL_Rect *new_tiles = (SDL_Rect*)malloc(sizeof(SDL_Rect) * (phraseLength));

		for (int i = 0; i < phraseLength; i++ ) {
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

		if( phraseLength > 0 ){
			posithioningChar();
		}
	}
}

bool Phrase::isAdmitted( char c ){
	switch ( selection ){
		case numbers_only:
			if ( c >= '0' && c <= '9' ) { return true; }
			return false;
		case no_special_char:
			if (c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') { return true; }
			return false;
		default:
			return true;
	}
}

void Phrase::render( SDL_Renderer* renderer ) {
	for (int i = 0; i < phraseLength; i++) {
		texture->render( renderer, &tiles[i], &posithions[i] );
	}
}

char Phrase::upperCase( char c ){
	if ('a' <= c && c <= 'z') {
		return c - 32;
	}
	return c;
}

int Phrase::getPhraseLength() {
	return phraseLength;
}
char* Phrase::getText() {
	return phrase;
}

Phrase::~Phrase() {
	delete texture;
	free(phrase);
	free(posithions);
	free(tiles);
}
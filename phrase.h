#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef unix
	#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

#ifndef PHRASE
#define PHRASE

#define IMAGE_CHAR_WIDTH_DIMENSION 7
#define IMAGE_CHAR_HEIGHT_DIMENSION 7

#define LAST_FIRST_ROW_CAHR 'P'

#define FIRST_ROW_Y_POSITION 86
#define SECOND_ROW_Y_POSITION 94
#define NUMBER_Y_POSITION 102

class Phrase{
public:
	Phrase( const char *phrase, int x, int y, int width, int height, SDL_Renderer* renderer );
	void addCharacter( char c );
	void removeLastCharacter();
	void render( SDL_Renderer *renderer );
private:
	Texture *texture;
	SDL_Rect *posithions, * tiles;
	int x, y, width, height, phraseLenght;

	void fromCharToImage( char c, int positionIndex );
	void posithioningChar();
	char upperCase( char c );
};

#endif
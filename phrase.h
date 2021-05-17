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

enum INPUT_TYPE {
	all,
	numbers_only,
	no_special_char
};

#define IMAGE_CHAR_WIDTH_DIMENSION 7
#define IMAGE_CHAR_HEIGHT_DIMENSION 7

#define LAST_FIRST_ROW_CAHR 'P'

#define FIRST_ROW_Y_POSITION 86
#define SECOND_ROW_Y_POSITION 94
#define NUMBER_Y_POSITION 102

class Phrase{
public:
	Phrase( const char *phrase, int x, int y, int width, int height, SDL_Renderer* renderer );
	Phrase( const char* phrase, int x, int y, int width, int height, int charDimension, SDL_Renderer* renderer );
	Phrase( const char* phrase, int x, int y, int width, int height, enum INPUT_TYPE selection, SDL_Renderer* renderer );
	Phrase( const char* phrase, int x, int y, int width, int height, int charDimension, enum INPUT_TYPE selection, SDL_Renderer* renderer );
	~Phrase();
	void addCharacter( char c );
	void removeLastCharacter();
	void render( SDL_Renderer *renderer );

	char *getText();
	int getPhraseLength();
private:
	Texture *texture;
	SDL_Rect *posithions, * tiles;
	char *phrase;
	int x, y, width, height, phraseLength, charDimension;
	bool dinamicTextDimension;

	enum INPUT_TYPE selection;

	void commonInitialization( const char* phrase, int x, int y, int width, int height, SDL_Renderer* renderer );
	void fromCharToImage( char c, int positionIndex );
	void posithioningChar();
	char upperCase( char c );
	bool isAdmitted( char c );
};

#endif
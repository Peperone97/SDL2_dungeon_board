#include "SDL2/include/SDL2/SDL.h"

#include "texture.h"
#include "phrase.h"

#ifndef BUTTON
#define BUTTON

class Button {
public:
	Button( const char* text, int x, int y, int width, int height, SDL_Renderer *renderer );
	~Button();
	bool isClicked( int x, int y );
	void isOnFocus( int x, int y );
	void render( SDL_Renderer *renderer );
	char *getText();
private:
	SDL_Rect tile, position, background_position, background_tile;
	Texture *texture;
	Phrase *text;
	bool focused;
	int stringLen( const char *s );
};

#endif
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef unix
	#include <SDL2/SDL.h>
#endif

#include "texture.h"
#include "phrase.h"

#ifndef BUTTON
#define BUTTON

class Button {
public:
	Button( const char* text, int x, int y, int width, int height, SDL_Renderer *renderer );
	~Button();
	bool isClicked( int x, int y );
	void render( SDL_Renderer *renderer );
private:
	SDL_Rect tile, position;
	Texture *texture;
	Phrase *text;
	int stringLen( const char *s );
};

#endif
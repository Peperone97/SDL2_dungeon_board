#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef unix
	#include <SDL2/SDL.h>
#endif

#include "button.h"
#include "phrase.h"
#include "texture.h"

#ifndef DROPDOWN_MENU
#define DROPDOWN_MENU

enum Event{ CLICK, MOTION };

class DropdownMenu {
public:
	DropdownMenu( int x, int y, int width, int height, SDL_Renderer *renderer );
	~DropdownMenu();
	void handleEvent( int x, int y, enum Event );
	void addEntry( const char *entry, SDL_Renderer *renderer );
	const char *getSelection();
	void render(SDL_Renderer *renderer);
	bool isActivate();
	void setText( const char *text );
	char* getSelectedText();
private:
	SDL_Rect tile, position;
	SDL_Rect arrow_tile, arrow_position;
	bool activate;

	int n_entries;
	Phrase *selection;
	Button **entries;
	Texture *texture;

};

#endif
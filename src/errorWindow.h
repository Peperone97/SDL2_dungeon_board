#include "SDL2/include/SDL2/SDL.h"
#include "SDL2/include/SDL2/SDL_image.h"

#include "baseWindow.h"
#include "phrase.h"

#ifndef ERROR_WINDOW
#define ERROR_WINDOW

class ErrorWindow : public BaseWindow{
public:
	ErrorWindow( const char* title, int width, int height );
	~ErrorWindow();
private:
	Phrase *error;

	void render();
	void eventManager();
};

#endif
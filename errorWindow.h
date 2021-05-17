#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#endif
#ifdef unix
	#include <SDL2/SDL.h>
	#include <SDL2/DL_image.h>
#endif

#include "baseWindow.h"
#include "phrase.h"

#ifndef ERROR_WINDOW
#define ERROR_WINDOW

class ErrorWindow : public BaseWindow{
public:
	ErrorWindow( const char* title, int width, int height );
	~ErrorWindow();
	void run();
private:
	Phrase *error;
	SDL_Thread *render_thread;

	static void render_wrapper(void* obj) {
		static_cast<ErrorWindow*>(obj)->render();
	}
	void render();
	void eventManager();
};

#endif
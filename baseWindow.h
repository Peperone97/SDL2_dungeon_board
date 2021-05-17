#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#endif
#ifdef unix
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#ifndef BASE_WINDOW
#define BASE_WINDOW

#define FPS 30
#define SECOND 1000

class BaseWindow {
public:
	BaseWindow( const char* title, int width, int height );
    ~BaseWindow();
    void show();

protected:
    int width, height;
    bool quit;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;

    //void eventManager();
    void close();
};

#endif
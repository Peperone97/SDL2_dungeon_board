#ifdef _WIN32
	#include "SDL2\include\SDL2\SDL.h"
#endif
#ifdef unix
	#include <SDL2/SDL.h>
#endif

#include "entity.h"
#include "timer.h"

#ifndef CURSOR
#define CURSOR

class Cursor : public Entity{
public:
	Cursor( int x, int y, int dim, SDL_Renderer *renderer );
	~Cursor();
	void render();
	void update();
private:
	bool is_visible;
};

#endif
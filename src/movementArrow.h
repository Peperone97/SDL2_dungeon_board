#ifdef _WIN32
	#include "SDL2\include\SDL2\SDL.h"
#endif
#ifdef unix
	#include <SDL2/SDL.h>
#endif

#include "entity.h"

#ifndef MOVEMENT_ARROW
#define MOVEMENT_ARROW

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class MovementArrow : public Entity {
public:
	MovementArrow( int x, int y, int dim, enum Direction orientation, SDL_Renderer* renderer );
	~MovementArrow();
	void update(){};
	void render();
private:
};

#endif
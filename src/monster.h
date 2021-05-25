#include "SDL2/include/SDL2/SDL.h"

#include "entity.h"
#include "timer.h"

#ifndef MONSTER
#define MONSTER

class Monster : public Entity{
public:
	Monster( int x, int y, int dim, SDL_Renderer *renderer );
	~Monster();
	void render();
	void update();
private:
	int sprite;
};

#endif
#ifdef _WIN32
    #include "SDL2\include\SDL2\SDL.h"
#endif
#ifdef unix
    #include <SDL2/SDL.h>
#endif

#include "entity.h"

#ifndef CROSS
#define CROSS

class Cross : public Entity{
public:
    Cross(int x, int y, int dim, SDL_Renderer* renderer);
    ~Cross();
    void update() {};
    void render();
private:

};

#endif
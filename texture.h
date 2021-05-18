#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#endif
#ifdef unix
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif

//#include "SDL2/include/SDL.h"

#ifndef TEXTURE
#define TEXTURE

class Texture{
public:
    Texture( const char *path, SDL_Renderer *renderer );
    ~Texture();
    void render( SDL_Renderer *renderer, SDL_Rect *clip, SDL_Rect *destination );
    void changeColor( uint8_t r, uint8_t g, uint8_t b );
    int getWidth();
    int getHeight();
private:
    SDL_Texture *texture;
};

#endif
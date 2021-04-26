#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef TEXTURE
#define TEXTURE

class Texture{
public:
    Texture( const char *path, SDL_Renderer *renderer );
    ~Texture();
    void render( SDL_Renderer *renderer, SDL_Rect *clip, SDL_Rect *destination );
    int getWidth();
    int getHeight();
private:
    SDL_Texture *texture;
    int width, height;
};

#endif
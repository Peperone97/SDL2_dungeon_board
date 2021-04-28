#include "core.h"

Core::Core( int width, int height, int tileDimesion, SDL_Renderer *renderer ){
    this->tileDimesion = tileDimesion;
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    
    destination = (SDL_Rect**)malloc( sizeof(SDL_Rect*) * (width/tileDimesion) );
    entities = (Entity***)malloc( sizeof(Entity**) * (width/tileDimesion) );
    for( int i = 0; i < width/tileDimesion; i++ ){
        destination[i] = (SDL_Rect*)malloc( sizeof(SDL_Rect) * (height/tileDimesion) );
        entities[i] = (Entity**)malloc( sizeof(Entity*) * (height/tileDimesion) );
    }

    for( int i = 0; i < width/tileDimesion; i++ ){
        for( int j = 0; j < height/tileDimesion; j++ ){
            destination[i][j].w = tileDimesion;
            destination[i][j].h = tileDimesion;
            destination[i][j].x = i * tileDimesion;
            destination[i][j].y = j * tileDimesion;
            
            entities[i][j] = nullptr;
        }
    }

    for( int i = 0; i < 4; i++ ){
        tiles[i] = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    }
    //first tile
    tiles[0]->x = 161;
    tiles[0]->y = 1;
    tiles[0]->w = 38;
    tiles[0]->h = 38;
    //second tile
    tiles[1]->x = 201;
    tiles[1]->y = 1;
    tiles[1]->w = 38;
    tiles[1]->h = 38;
    //third tile
    tiles[2]->x = 241;
    tiles[2]->y = 1;
    tiles[2]->w = 38;
    tiles[2]->h = 38;
    //fourth tile
    tiles[3]->x = 161;
    tiles[3]->y = 41;
    tiles[3]->w = 38;
    tiles[3]->h = 38;

    texture = new Texture( "img/floor.png", renderer );
}

void Core::render(){
    int i = 0, j = 0;
    for( i = 0; i < width/tileDimesion; i++ ){
        for( j = 0; j < height/tileDimesion; j++ ){
            texture->render( renderer, tiles[1], &destination[i][j] );
            if( entities[i][j] != nullptr ){
                entities[i][j]->render();
            //printf("%d, %d\n", i, j);
        }
        }
    }
}
void Core::update(){
    int i = 0, j = 0;
    for( i = 0; i < width/tileDimesion; i++ ){
        for( j = 0; j < height/tileDimesion; j++ ){
            if( entities[i][j] != nullptr ){
                //printf("%d, %d\n", destination[i][j].x, destination[i][j].y);
                entities[i][j]->update();
            }
        }
    }
}

void Core::handleEvent( int x, int y ){
    int i = x/destination[0][0].w, j = y/destination[0][0].w;
    //printf("(%d, %d)\n%d, %d\n", x, y, destination[i][j].x, destination[i][j].y);
    if( entities[i][j] == nullptr ){
        int pos_x = destination[i][j].x + ((tileDimesion)-(tileDimesion*3/4))/2;
        int pos_y = destination[i][j].y + ((tileDimesion)-(tileDimesion*3/4))/2;
        entities[i][j] = new Entity( "img/skeletons2.png", renderer );
        entities[i][j]->addEntity( tileDimesion*3/4, pos_x, pos_y );
    }else{
        delete entities[i][j];
        entities[i][j] = nullptr;
    }
}

void Core::zoomIn( int x, int y ){
    if( tileDimesion * (zoomLevel + 1) <= width && tileDimesion * (zoomLevel + 1) <= height ){
        if( zoomLevel == 0 ){
            pos_i = x/destination[0][0].w;
            pos_j = y/destination[0][0].w;
        }
        zoomLevel++;
        printf("%d, %d\n", pos_i, pos_j);
        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                destination[i][j].w += tileDimesion;
                destination[i][j].h += tileDimesion;

                if( destination[i][j].x < destination[pos_i][pos_j].x ){
                    destination[i][j].x -= destination[i][j].w/(zoomLevel+1);
                }else if( destination[i][j].x > destination[pos_i][pos_j].x ){
                    destination[i][j].x += destination[i][j].w/(zoomLevel+1);
                }
                
                if( destination[i][j].y < destination[pos_i][pos_j].y ){
                    destination[i][j].y -= destination[i][j].h/(zoomLevel+1);
                }else if( destination[i][j].y > destination[pos_i][pos_j].y ){
                    destination[i][j].y += destination[i][j].h/(zoomLevel+1);
                }
            }
        }
    }
}

void Core::zoomOut( int x, int y ){
    if( zoomLevel > 0 ){
        //int pos_i = x/destination[0][0].w, pos_j = y/destination[0][0].w;
        
        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                if( destination[i][j].x < destination[pos_i][pos_j].x ){
                    destination[i][j].x += destination[i][j].w/(zoomLevel+1);
                }else if( destination[i][j].x > destination[pos_i][pos_j].x ){
                    destination[i][j].x -= destination[i][j].w/(zoomLevel+1);
                }
                
                if( destination[i][j].y < destination[pos_i][pos_j].y ){
                    destination[i][j].y += destination[i][j].h/(zoomLevel+1);
                }else if( destination[i][j].y > destination[pos_i][pos_j].y ){
                    destination[i][j].y -= destination[i][j].h/(zoomLevel+1);
                }

                destination[i][j].w -= tileDimesion;
                destination[i][j].h -= tileDimesion;
            }
        }

        zoomLevel--;
    }
}

Core::~Core(){
    for( int i = 0; i < width/tileDimesion; i++ ){
        free(destination[i]);
    }
    free(destination);
    for( int i = 0; i < 4; i++ ){
        free(tiles[i]);
    }
    delete texture;
}
#include "core.h"

Core::Core( int width, int height, int tileDimesion, SDL_Renderer *renderer ){
    this->tileDimesion = tileDimesion;
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    zoomLevel = 0;
    
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
    int *pos = pointOfClick(x, y);
    //printf("(%d, %d)\n%d, %d\n", x, y, destination[i][j].x, destination[i][j].y);
    if( entities[pos[0]][pos[1]] == nullptr ){
        int pos_x = destination[pos[0]][pos[1]].x + ((destination[0][0].w)-(destination[0][0].w*3/4))/2;
        int pos_y = destination[pos[0]][pos[1]].y + ((destination[0][0].w)-(destination[0][0].w*3/4))/2;
        entities[pos[0]][pos[1]] = new Entity( "img/skeletons2.png", renderer );
        entities[pos[0]][pos[1]]->addEntity( destination[0][0].w*3/4, pos_x, pos_y );
    }else{
        delete entities[pos[0]][pos[1]];
        entities[pos[0]][pos[1]] = nullptr;
    }
}

int* Core::pointOfClick( int x, int y ){ // find the i and j with linear search
    int i = width/tileDimesion / 2;
    int j = width/tileDimesion / 2;
    int *pos = (int*)malloc( sizeof(int) * 2 );
    while( destination[i][j].x > x || destination[i][j].w + destination[i][j].x < x ){
        if( destination[i][j].x > x ){
            i--;
        }else if( destination[i][j].x < x ){
            i++;
        }
    }
    pos[0] = i;
    while( destination[i][j].y > y || destination[i][j].h + destination[i][j].y < y ){
        if( destination[i][j].y > y ){
            j--;
        }else if( destination[i][j].y < y ){
            j++;
        }
    }
    pos[1] = j;
    printf("%d, %d\n", i, j);
    return pos;
}

void Core::zoomIn( int x, int y ){
    if( destination[pos_i][pos_j].w <= width/3 && destination[pos_i][pos_j].h <= height/3 ){
        
        /*if( zoomLevel == 0 ){ //set the tile zoom position
            pos_i = x/destination[0][0].w;
            pos_j = y/destination[0][0].w;
        }*/

        zoomLevel++;

        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                destination[i][j].w += tileDimesion;
                destination[i][j].h += tileDimesion;

                if( destination[i][j].x < destination[pos_i][pos_j].x ){
                    destination[i][j].x = destination[pos_i][pos_j].x - destination[i][j].w * (pos_i - i);
                }else if( destination[i][j].x > destination[pos_i][pos_j].x ){
                    destination[i][j].x = destination[pos_i][pos_j].x + destination[i][j].w * (i - pos_i);
                }
                
                if( destination[i][j].y < destination[pos_i][pos_j].y ){
                    destination[i][j].y = destination[pos_i][pos_j].y - destination[i][j].h * (pos_j - j);
                }else if( destination[i][j].y > destination[pos_i][pos_j].y ){
                    destination[i][j].y = destination[pos_i][pos_j].y + destination[i][j].h * (j - pos_j);
                }

                //zoom in entity
                if( entities[i][j] != nullptr ){
                    int pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                    int pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                    entities[i][j]->updateDimension( destination[i][j].w*3/4 );
                    entities[i][j]->updatePosition( pos_x, pos_y );
                }
            }
        }
    }
}

void Core::zoomOut( int x, int y ){
    if( zoomLevel > 0 ){
        
        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                destination[i][j].w -= tileDimesion;
                destination[i][j].h -= tileDimesion;

                if( destination[i][j].x < destination[pos_i][pos_j].x ){
                    destination[i][j].x = destination[pos_i][pos_j].x - destination[i][j].w * (pos_i - i);
                }else if( destination[i][j].x > destination[pos_i][pos_j].x ){
                    destination[i][j].x = destination[pos_i][pos_j].x + destination[i][j].w * (i - pos_i);
                }
                
                if( destination[i][j].y < destination[pos_i][pos_j].y ){
                    destination[i][j].y = destination[pos_i][pos_j].y - destination[i][j].h * (pos_j - j);
                }else if( destination[i][j].y > destination[pos_i][pos_j].y ){
                    destination[i][j].y = destination[pos_i][pos_j].y + destination[i][j].h * (j - pos_j);
                }    

                //zoom out entity
                if( entities[i][j] != nullptr ){
                    int pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                    int pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                    entities[i][j]->updateDimension( destination[i][j].w*3/4 );
                    entities[i][j]->updatePosition( pos_x, pos_y );
                }            
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
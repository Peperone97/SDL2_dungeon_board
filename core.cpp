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

    //what render?
    render_first_index_x = 0;
    render_first_index_y = 0;
    render_last_index_x =  width/tileDimesion - 1;
    render_last_index_y = height/tileDimesion -1;

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
    //printf("Tiles:\n");
    for( i = render_first_index_x; i <= render_last_index_x; i++ ){
        for( j = render_first_index_y; j <= render_last_index_y; j++ ){
            texture->render( renderer, tiles[1], &destination[i][j] );
            if( entities[i][j] != nullptr ){
                entities[i][j]->render();
            }
            //printf("%d, %d\n", i, j);
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
    //pos[0] is the x value, pos[1] is the y
    int *pos = pointOfClick(x, y); // find the tile where click is append

    if( entities[pos[0]][pos[1]] == nullptr ){
        int pos_x = destination[pos[0]][pos[1]].x + ((destination[0][0].w)-(destination[0][0].w*3/4))/2;
        int pos_y = destination[pos[0]][pos[1]].y + ((destination[0][0].w)-(destination[0][0].w*3/4))/2;
        entities[pos[0]][pos[1]] = new Entity( "img/skeletons2.png", renderer );
        entities[pos[0]][pos[1]]->addEntity( destination[0][0].w*3/4, pos_x, pos_y );
    }else{
        delete entities[pos[0]][pos[1]];
        entities[pos[0]][pos[1]] = nullptr;
    }

    free(pos);
}

int* Core::pointOfClick( int x, int y ){ // find the i and j with linear search
    //pos[0] is the x value, pos[1] is the y
    int i = ( render_first_index_x + render_last_index_x ) / 2;
    int j = ( render_first_index_y + render_last_index_y ) / 2;
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
    return pos;
}

void Core::zoomIn( int x, int y ){
    //pos[0] is the x value, pos[1] is the y
    printf("Zoom in\n%d, %d, %d, %d\n", render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y);
    int *pos = pointOfClick(x, y);
    pos_i = pos[0];
    pos_j = pos[1];
    free(pos);
    if( destination[pos_i][pos_j].w <= width/3 && destination[pos_i][pos_j].h <= height/3 ){
        int pos_x, pos_y;

        zoomLevel++;

        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                destination[i][j].w += tileDimesion;
                destination[i][j].h += tileDimesion;

                if( destination[i][j].x < destination[pos_i][pos_j].x ){ //go left
                    destination[i][j].x = destination[pos_i][pos_j].x - destination[i][j].w * (pos_i - i);
                    if( destination[i][j].x + destination[i][j].w  <= 0 ){ // is on screen?
                        render_first_index_x = i + 1;
                    }
                }else if( destination[i][j].x > destination[pos_i][pos_j].x ){ //go right
                    destination[i][j].x = destination[pos_i][pos_j].x + destination[i][j].w * (i - pos_i);
                    if( destination[i][j].x < width ){ // is on screen?
                        render_last_index_x = i;
                    }
                }
                
                if( destination[i][j].y < destination[pos_i][pos_j].y ){ //go up
                    destination[i][j].y = destination[pos_i][pos_j].y - destination[i][j].h * (pos_j - j);
                    if( destination[i][j].y + destination[i][j].h  <= 0 ){ // is on screen?
                        render_first_index_y = j + 1;
                    }
                }else if( destination[i][j].y > destination[pos_i][pos_j].y ){ //go down
                    destination[i][j].y = destination[pos_i][pos_j].y + destination[i][j].h * (j - pos_j);
                    if( destination[i][j].y < height ){ // is on screen?
                        render_last_index_y = j;
                    }
                }

                //zoom in entity
                if( entities[i][j] != nullptr ){
                    pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                    pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                    entities[i][j]->updateDimension( destination[i][j].w*3/4 );
                    entities[i][j]->updatePosition( pos_x, pos_y );
                }
            }
        }
    }
    printf("%d, %d, %d, %d\n", render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y);
}

void Core::zoomOut( int x, int y ){
    int pos_x, pos_y;
    printf("Zoom Out\n%d, %d, %d, %d\n", render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y);
    if( zoomLevel > 1 ){
        //pos[0] is the x value, pos[1] is the y
        int *pos = pointOfClick(x, y);
        int pos_i = pos[0];
        int pos_j = pos[1];
        free(pos);

        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                destination[i][j].w -= tileDimesion;
                destination[i][j].h -= tileDimesion;

                if( destination[i][j].x < destination[pos_i][pos_j].x ){ //dezoom left
                    destination[i][j].x = destination[pos_i][pos_j].x - destination[i][j].w * (pos_i - i);
                    if( destination[i][j].x + destination[i][j].w  <= 0 ){ // is on screen?
                        render_first_index_x = i - 1;
                    }
                }else if( destination[i][j].x > destination[pos_i][pos_j].x ){  //dezoom right
                    destination[i][j].x = destination[pos_i][pos_j].x + destination[i][j].w * (i - pos_i);
                    if( destination[i][j].x >= width ){ // is on screen?
                        render_last_index_x = i;
                    }
                }
                
                if( destination[i][j].y < destination[pos_i][pos_j].y ){ //dezoom up
                    destination[i][j].y = destination[pos_i][pos_j].y - destination[i][j].h * (pos_j - j);
                    if( destination[i][j].y + destination[i][j].h  <= 0 ){ // is on screen?
                        render_first_index_y = j - 1;
                    }
                }else if( destination[i][j].y > destination[pos_i][pos_j].y ){ //dezoom down
                    destination[i][j].y = destination[pos_i][pos_j].y + destination[i][j].h * (j - pos_j);
                    if( destination[i][j].y >= height ){ // is on screen?
                        render_last_index_y = j;
                    }
                }    

                //zoom out entity
                if( entities[i][j] != nullptr ){
                    pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                    pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                    entities[i][j]->updateDimension( destination[i][j].w*3/4 );
                    entities[i][j]->updatePosition( pos_x, pos_y );
                }            
            }
        }

        zoomLevel--;
    }else if( zoomLevel == 1 ){ //for fixing dezoom bug
        render_first_index_x = 0;
        render_first_index_y = 0;
        render_last_index_x =  width/tileDimesion - 1;
        render_last_index_y = height/tileDimesion -1;
        for( int i = 0; i < width/tileDimesion; i++ ){
            for( int j = 0; j < height/tileDimesion; j++ ){
                destination[i][j].w = tileDimesion;
                destination[i][j].h = tileDimesion;
                destination[i][j].x = i * tileDimesion;
                destination[i][j].y = j * tileDimesion;

                if( entities[i][j] != nullptr ){
                    pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                    pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                    entities[i][j]->updateDimension( destination[i][j].w*3/4 );
                    entities[i][j]->updatePosition( pos_x, pos_y );
                }
            }
        }
        zoomLevel--;
    }
    printf("%d, %d, %d, %d\n", render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y);
}

void Core::moveMap( int x_move, int y_move ){
    printf("Move\n%d, %d, %d, %d\n", render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y);
    int pos_x, pos_y;
    if( destination[0][0].x + x_move > 0 ){ //i can't go more to left
        x_move = - destination[0][0].x;
    }
    if( destination[width/tileDimesion - 1][height/tileDimesion - 1].x + destination[width/tileDimesion - 1][height/tileDimesion - 1].w <= width - x_move ){ //i can't go more to right
        x_move = width - destination[width/tileDimesion - 1][height/tileDimesion - 1].x - destination[width/tileDimesion - 1][height/tileDimesion - 1].w;
    }
    if( destination[0][0].y + y_move > 0 ){ //i can't go more up
        y_move = - destination[0][0].y;
    }
    if( destination[width/tileDimesion - 1][height/tileDimesion - 1].y + destination[width/tileDimesion - 1][height/tileDimesion - 1].h <= height - y_move ){ //i can't go more down
        y_move = height - destination[height/tileDimesion - 1][height/tileDimesion - 1].y - destination[width/tileDimesion - 1][height/tileDimesion - 1].h;
    }
    for( int i = 0; i < width/tileDimesion; i++ ){
        for( int j = 0; j < height/tileDimesion; j++ ){
            destination[i][j].x += x_move;
            destination[i][j].y += y_move;
            //move entities
            if( entities[i][j] != nullptr){
                pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                entities[i][j]->updatePosition( pos_x, pos_y );
            }
        }
    }
    //update render index   
    //left 
    if( destination[render_first_index_x][0].x > 0 ){
        render_first_index_x--;
    }else if( destination[render_first_index_x][0].x + destination[render_first_index_x][0].w < 0 ){
        render_first_index_x++;
    }
    //up
    if( destination[0][render_first_index_y].y > 0 ){
        render_first_index_y--;
    }else if( destination[0][render_first_index_y].y + destination[0][render_first_index_y].h < 0 ){
        render_first_index_y++;
    }
    //right
    if( destination[render_last_index_x][0].x + destination[render_last_index_x][0].w < width ){
        render_last_index_x++;
    }else if( destination[render_last_index_x][0].x > width ){
        render_last_index_x--;
    }
    //down
    printf("%d %d %d %d\n", destination[0][render_last_index_y].y, destination[0][render_last_index_y].h, destination[0][render_last_index_y].y+destination[0][render_last_index_y].h, height);
    if( destination[0][render_last_index_y].y + destination[0][render_last_index_y].h < height ){
        render_last_index_y++;
    }else if( destination[0][render_last_index_y].y > height ){
        render_last_index_y--;
    }
    printf("%d, %d, %d, %d\n", render_first_index_x, render_first_index_y, render_last_index_x, render_last_index_y);
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
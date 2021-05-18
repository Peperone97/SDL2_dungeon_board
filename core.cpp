#include "core.h"

Core::Core( int width, int height, int tileDimension, SDL_Renderer *renderer ){
    this->tileDimesion = tileDimension;
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    zoomLevel = 0;
    dim_i = width/tileDimension;
    dim_j = width/tileDimension;
    //random
    time_t t;
    srand(time(&t));

    destination = (SDL_Rect**)malloc( sizeof(SDL_Rect*) * (dim_i) );
    entities = (Entity***)malloc( sizeof(Entity**) * (dim_i) );
    typeOfTile = (int**)malloc( sizeof(int*) * (dim_i) );
    map = (int**)malloc( sizeof(int*) * (dim_i) );
    for( int i = 0; i < dim_i; i++ ){
        destination[i] = (SDL_Rect*)malloc( sizeof(SDL_Rect) * (dim_j) );
        entities[i] = (Entity**)malloc( sizeof(Entity*) * (dim_j) );
        typeOfTile[i] = (int*)malloc( sizeof(int) * (dim_j) );
        map[i] = (int*)malloc( sizeof(int) * (dim_j) );
    }
    
    //create the map
    createMap( map, dim_i );

    for( int i = 0; i < dim_i; i++ ){
        for( int j = 0; j < dim_j; j++ ){
            destination[i][j].w = tileDimension;
            destination[i][j].h = tileDimension;
            destination[i][j].x = i * tileDimension;
            destination[i][j].y = j * tileDimension;
            
            typeOfTile[i][j] = rand() % 4;

            entities[i][j] = nullptr;

        }
    }

    //what render?
    render_first_index_x = 0;
    render_first_index_y = 0;
    render_last_index_x =  dim_i - 1;
    render_last_index_y = dim_j -1;

    for( int i = 0; i < 4; i++ ){
        tiles[i] = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    }

    text = new Phrase( "Pre-alpha 1.0", 4, 4, 100, 100, renderer );

    //first tile
    tiles[0]->x = 0;
    tiles[0]->y = 0;
    tiles[0]->w = 38;
    tiles[0]->h = 38;
    //second tile
    tiles[1]->x = 38;
    tiles[1]->y = 0;
    tiles[1]->w = 38;
    tiles[1]->h = 38;
    //third tile
    tiles[2]->x = 76;
    tiles[2]->y = 0;
    tiles[2]->w = 38;
    tiles[2]->h = 38;
    //fourth tile
    tiles[3]->x = 114;
    tiles[3]->y = 0;
    tiles[3]->w = 38;
    tiles[3]->h = 38;

    texture = new Texture( "img/sprites.png", renderer );

}

void Core::render(){
    int i = 0, j = 0;
    //for (i = render_first_index_x; i <= render_last_index_x; i++) {
        //for (j = render_first_index_y; j <= render_last_index_y; j++) {
    for (i = 0; i < dim_i; i++) {
        for (j = 0; j < dim_j; j++) {
            if( map[i][j] ){
                texture->render( renderer, tiles[typeOfTile[i][j]], &destination[i][j] );
                if( entities[i][j] != nullptr && isVisible( i, j ) ){
                    entities[i][j]->render();
                }
            }
        }
    }
    text->render( renderer );
}
void Core::update(){
    int i = 0, j = 0;
    for( i = 0; i < dim_i; i++ ){
        for( j = 0; j < dim_j; j++ ){
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

    if( map[pos[0]][pos[1]] ){
        //printf("%d, %d\n", pos[0], pos[1]);
        if( entities[pos[0]][pos[1]] == nullptr ){
            int pos_x = destination[pos[0]][pos[1]].x + ((destination[0][0].w)-(destination[0][0].w*3/4))/2;
            int pos_y = destination[pos[0]][pos[1]].y + ((destination[0][0].w)-(destination[0][0].w*3/4))/2;
            //entities[pos[0]][pos[1]] = new Entity( "img/sprites.png", renderer );
            //entities[pos[0]][pos[1]]->addEntity( destination[0][0].w*3/4, pos_x, pos_y );
            entities[pos[0]][pos[1]] = new Monster( pos_x, pos_y, destination[0][0].w * 3 / 4, renderer );
        }else{
            delete entities[pos[0]][pos[1]];
            entities[pos[0]][pos[1]] = nullptr;
        }
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
    int *pos = pointOfClick(x, y);
    int pos_i = pos[0];
    int pos_j = pos[1];
    free(pos);
    if( destination[pos_i][pos_j].w <= width/3 && destination[pos_i][pos_j].h <= height/3 ){
        int pos_x, pos_y;
        int zoomRes = destination[0][0].w + tileDimesion;

        zoomLevel++;
        do {
            for (int i = 0; i < dim_i; i++) {
                for (int j = 0; j < dim_j; j++) {
                    destination[i][j].w += 1;
                    destination[i][j].h += 1;

                    if (destination[i][j].x < destination[pos_i][pos_j].x) { //go left
                        destination[i][j].x = destination[pos_i][pos_j].x - destination[i][j].w * (pos_i - i);
                    }
                    else if (destination[i][j].x > destination[pos_i][pos_j].x) { //go right
                        destination[i][j].x = destination[pos_i][pos_j].x + destination[i][j].w * (i - pos_i);
                    }

                    if (destination[i][j].y < destination[pos_i][pos_j].y) { //go up
                        destination[i][j].y = destination[pos_i][pos_j].y - destination[i][j].h * (pos_j - j);
                    }
                    else if (destination[i][j].y > destination[pos_i][pos_j].y) { //go down
                        destination[i][j].y = destination[pos_i][pos_j].y + destination[i][j].h * (j - pos_j);
                    }

                    //zoom in entity
                    if (entities[i][j] != nullptr) {
                        pos_x = destination[i][j].x + ((destination[i][j].w) - (destination[i][j].w * 3 / 4)) / 2;
                        pos_y = destination[i][j].y + ((destination[i][j].h) - (destination[i][j].h * 3 / 4)) / 2;
                        entities[i][j]->updateDimension(destination[i][j].w * 3 / 4);
                        entities[i][j]->updatePosition(pos_x, pos_y);
                    }
                }
            }
            SDL_Delay(5);
        } while( destination[0][0].w != zoomRes );
        updateVisiblesIndex();
    }
}

void Core::zoomOut( int x, int y ){
    int pos_x, pos_y;
    
    if( zoomLevel > 0 ){
        //pos[0] is the x value, pos[1] is the y
        int *pos = pointOfClick(x, y);
        int pos_i = pos[0];
        int pos_j = pos[1];
        free(pos);

        int zoomRes = destination[0][0].w - tileDimesion;

        do {
            for (int i = 0; i < dim_i; i++) {
                for (int j = 0; j < dim_j; j++) {
                    destination[i][j].w -= 1;
                    destination[i][j].h -= 1;

                    if (destination[i][j].x < destination[pos_i][pos_j].x) { //dezoom left
                        destination[i][j].x = destination[pos_i][pos_j].x - destination[i][j].w * (pos_i - i);
                    }
                    else if (destination[i][j].x > destination[pos_i][pos_j].x) {  //dezoom right
                        destination[i][j].x = destination[pos_i][pos_j].x + destination[i][j].w * (i - pos_i);
                    }

                    if (destination[i][j].y < destination[pos_i][pos_j].y) { //dezoom up
                        destination[i][j].y = destination[pos_i][pos_j].y - destination[i][j].h * (pos_j - j);
                    }
                    else if (destination[i][j].y > destination[pos_i][pos_j].y) { //dezoom down
                        destination[i][j].y = destination[pos_i][pos_j].y + destination[i][j].h * (j - pos_j);
                    }

                    //zoom out entity
                    if (entities[i][j] != nullptr) {
                        pos_x = destination[i][j].x + ((destination[i][j].w) - (destination[i][j].w * 3 / 4)) / 2;
                        pos_y = destination[i][j].y + ((destination[i][j].h) - (destination[i][j].h * 3 / 4)) / 2;
                        entities[i][j]->updateDimension(destination[i][j].w * 3 / 4);
                        entities[i][j]->updatePosition(pos_x, pos_y);
                    }
                }
            }
            SDL_Delay(5);
        }while(destination[0][0].w != zoomRes);
        zoomLevel--;

        //the tiles are bad positioned? Fix it
        bool outOfIndex_x = 0, outOfIndex_y = 0;
        int change_x = 0, change_y = 0;

        if( destination[0][0].x > 0 ){
            outOfIndex_x = true;
            change_x = - destination[0][0].x;
        }
        if( destination[0][0].y > 0 ){
            outOfIndex_y = true;
            change_y = - destination[0][0].y;
        }
        if( destination[dim_i - 1][dim_j - 1].x + destination[dim_i - 1][dim_j - 1].w < width ){
            outOfIndex_x = true;
            change_x = width - ( destination[dim_i - 1][dim_j - 1].x + destination[dim_i - 1][dim_j - 1].w );
        }
        if( destination[dim_i - 1][dim_j - 1].y + destination[dim_i - 1][dim_j - 1].h < height ){
            outOfIndex_y = true;
            change_y = height - ( destination[dim_i - 1][dim_j - 1].y + destination[dim_i - 1][dim_j - 1].h );
        }
        //fix the positions
        if( outOfIndex_x || outOfIndex_y ){
            for( int i = 0; i < dim_i; i++ ){
                for( int j = 0; j < dim_j; j++ ){
                    destination[i][j].x += change_x;
                    destination[i][j].y += change_y;

                    //update entity positions
                    if( entities[i][j] != nullptr ){
                        pos_x = destination[i][j].x + ((destination[i][j].w)-(destination[i][j].w*3/4))/2;
                        pos_y = destination[i][j].y + ((destination[i][j].h)-(destination[i][j].h*3/4))/2;
                        entities[i][j]->updatePosition( pos_x, pos_y );
                    }
                }
            }
        }

        updateVisiblesIndex();

    }
}

void Core::moveMap( int x_move, int y_move ){
    int pos_x, pos_y;
    if( destination[0][0].x + x_move > 0 ){ //i can't go more to left
        x_move = - destination[0][0].x;
    }
    if( destination[dim_i - 1][dim_j - 1].x + destination[dim_i - 1][dim_j - 1].w <= width - x_move ){ //i can't go more to right
        x_move = width - destination[dim_i - 1][dim_j - 1].x - destination[dim_i - 1][dim_j - 1].w;
    }
    if( destination[0][0].y + y_move > 0 ){ //i can't go more up
        y_move = - destination[0][0].y;
    }
    if( destination[dim_i - 1][dim_j - 1].y + destination[dim_i - 1][dim_j - 1].h <= height - y_move ){ //i can't go more down
        y_move = height - destination[dim_j - 1][dim_j - 1].y - destination[dim_i - 1][dim_j - 1].h;
    }
    for( int i = 0; i < dim_i; i++ ){
        for( int j = 0; j < dim_j; j++ ){
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

    updateVisiblesIndex();
}

bool Core::isOnTopOfTheScreen( int i, int j ){
    if( ( destination[i][j].x + destination[i][j].w > 0 ) ||  //the x is on screen?
        ( destination[i][j].y + destination[i][j].h > 0 ) ){ //the y is on screen?
        return true;
    }
    return false;
}

bool Core::isOnBottomOfTheScreen( int i, int j ){
    if( ( destination[i][j].x < width ) ||  //the x is on screen?
        ( destination[i][j].y < height ) ){ //the y is on screen?
        return true;
    }
    return false;
}

bool Core::isVisible( int i, int j ){
    
    if( render_first_index_x <= i && render_last_index_x >= i ){
        if( render_first_index_y <= j && render_last_index_y >= j ){
            return true;
        }
    }
    return false;
}

void Core::updateVisiblesIndex(){
    for( int i = 0; i < dim_i; i++ ){
        for( int j = 0; j < dim_j; j++ ){
            //update first index
            if( isOnTopOfTheScreen( i, j ) ){
                if( render_first_index_x > i ){
                    render_first_index_x = i;
                }
                if( render_first_index_y > j ){
                    render_first_index_y = j;
                }
            }else{
                render_first_index_x = i + 1;
                render_first_index_y = j + 1;
            }
            //update last index
            if( isOnBottomOfTheScreen( i, j ) ){
                if( render_last_index_x < i ){
                    render_last_index_x = i;
                }
                if( render_last_index_y < j ){
                    render_last_index_y = j;
                }
            }else{
                render_last_index_x = i - 1;
                render_last_index_y = j - 1;
            }
        }
    }
}

void Core::createNewDungeon(){
    for( int i = 0; i < dim_i; i++ ){
        for( int j = 0; j < dim_j; j++ ){
            if( entities[i][j] != nullptr ){
                delete entities[i][j];
                entities[i][j] = nullptr;
            }
        }
    }
    createMap( map, dim_i );
}

Core::~Core(){
    for( int i = 0; i < dim_i; i++ ){
        free(destination[i]);
        free(entities[i]);
        free(typeOfTile[i]);
        free(map[i]);
    }
    free(destination);
    free(entities);
    free(typeOfTile);
    free(map);
    for( int i = 0; i < 4; i++ ){
        free(tiles[i]);
    }
    delete texture;
}
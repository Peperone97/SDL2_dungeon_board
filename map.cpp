#include "map.h"

bool isBlocked( int **map, struct room room ){

    for( int i = room.x; i <= room.x+room.w; i++ ){ // the room is isolated ?
        for( int d = 0; d <= ROOM_MIN_DISTANCE; d++ ){
            if( map[i][room.y - d] == 1 ){ // left 
                return true;
            }
            if( map[i][room.y+room.h + d] == 1 ){ // right
                return true;
            }
        }
    }
    for( int j = room.y; j <= room.y+room.h; j++ ){ // the room is isolated ?
        for( int d = 0; d <= ROOM_MIN_DISTANCE; d++ ){
            if( map[room.x - d][j] == 1 ){ // up
                return true;
            }
            if( map[room.x+room.w + d][j] == 1 ){ // down
                return true;
            }
        }
    }
    for( int d = 0; d <= ROOM_MIN_DISTANCE; d++ ){ //diagonals
            if( map[room.x - d][room.y - d] == 1 ){ //left up
                return true;
            }
            if( map[room.x+room.w + d][room.y - d] == 1 ){ //right up
                return true;
            }
            if( map[room.x - d][room.y+room.h + d] == 1 ){ //left down
                return true;
            }
            if( map[room.x+room.w + d][room.y+room.h + d] == 1 ){ //right down
                return true;
            }
        }

    return false;
}

bool isOnMap( struct room *room, int dim){
    if( ( room->x >= 0 && room->y >= 0 ) && ( (room->x+room->w + ROOM_MIN_DISTANCE) < dim && (room->y+room->h + ROOM_MIN_DISTANCE) < dim ) ){
        return true;
    }
    return false;
}

struct room initRoom( int dim ){
    int room_max_dimension = dim*20/100;

    struct room *room = (struct room*)malloc( sizeof( struct room ) );

    do{
        room->x = rand()%(dim - ROOM_MIN_DISTANCE) + ROOM_MIN_DISTANCE;
        room->y = rand()%(dim - ROOM_MIN_DISTANCE) + ROOM_MIN_DISTANCE;
        room->w = rand()%(room_max_dimension - MIN_ROOM_DIMENSION) + MIN_ROOM_DIMENSION;
        room->h = rand()%(room_max_dimension - MIN_ROOM_DIMENSION) + MIN_ROOM_DIMENSION;
    }while( !isOnMap( room, dim ) );

    return *room;
}

struct room* createRooms( int** map, int dim, int *n_rooms ){
    time_t t;
    srand( time(&t) );

    do{
        *n_rooms = rand()%dim;  
    }while( *n_rooms <= dim*12/100 || *n_rooms >= dim*27/100 );

    struct room *rooms = (struct room*)malloc( sizeof(struct room) * (*n_rooms+1) );

    for( int r = 0; r <= *n_rooms; r++ ){
        
        do{
            rooms[r] = initRoom( dim );
        }while( isBlocked( map, rooms[r] ) );
        // draw the room on map
        for( int i = rooms[r].x; i <= rooms[r].x+rooms[r].w; i++ ){
            for( int j = rooms[r].y; j <= rooms[r].y+rooms[r].h; j++ ){
                map[i][j] = 1;
            }
        }

    }

    return rooms;

}

void createCorridos( int **map, int dim, struct room *rooms, int n_rooms ){
    int n_doors, room_to_connect, random_flag;
    int **center_of_rooms = (int**)malloc( sizeof(int*) * (n_rooms+1));

    for( int r = 0; r <= n_rooms; r++ ){
        center_of_rooms[r] = (int*)malloc( sizeof(int*) * 2);
        center_of_rooms[r][0] = rooms[r].w/2 + rooms[r].x;
        center_of_rooms[r][1] = rooms[r].h/2 + rooms[r].y;
    }
    for( int r = 0; r <= n_rooms; r++ ){
        n_doors = rand()%4 + 1;
        for( int d = 0; d < n_doors; d++ ){
            room_to_connect = rand()%(n_rooms+1);

            random_flag = rand()%2;

            if( random_flag ){
                do{
                    if( center_of_rooms[r][0] < center_of_rooms[room_to_connect][0] ){
                        map[center_of_rooms[r][0]++][center_of_rooms[r][1]] = 1;
                    }else{
                        map[center_of_rooms[r][0]--][center_of_rooms[r][1]] = 1;
                    }
                }while( center_of_rooms[r][0] != center_of_rooms[room_to_connect][0] );
                do{
                    if( center_of_rooms[r][1] < center_of_rooms[room_to_connect][1] ){
                        map[center_of_rooms[r][0]][center_of_rooms[r][1]++] = 1;
                    }
                    else{
                        map[center_of_rooms[r][0]][center_of_rooms[r][1]--] = 1;
                    }
                }while( center_of_rooms[r][1] != center_of_rooms[room_to_connect][1] );
            }else{
                do{
                    if( center_of_rooms[r][1] < center_of_rooms[room_to_connect][1] ){
                        map[center_of_rooms[r][0]][center_of_rooms[r][1]++] = 1;
                    }
                    else{
                        map[center_of_rooms[r][0]][center_of_rooms[r][1]--] = 1;
                    }
                }while( center_of_rooms[r][1] != center_of_rooms[room_to_connect][1] );
                do{
                    if( center_of_rooms[r][0] < center_of_rooms[room_to_connect][0] ){
                        map[center_of_rooms[r][0]++][center_of_rooms[r][1]] = 1;
                    }else{
                        map[center_of_rooms[r][0]--][center_of_rooms[r][1]] = 1;
                    }
                }while( center_of_rooms[r][0] != center_of_rooms[room_to_connect][0] );
            }
        }
    }

    for( int r = 0; r <= n_rooms; r++ ){
        free(center_of_rooms[r]);
    }
    free(center_of_rooms);

}

void createMap( int **map, int dim ){

    //max_room_dimension = dim * 20/100;

    for( int i = 0; i < dim; i++ ){
        for( int j = 0; j < dim; j++ ){
            map[i][j] = 0;
        }
    }

    int n_rooms;
    struct room *rooms = createRooms( map, dim, &n_rooms );

    createCorridos( map, dim, rooms, n_rooms );

    free(rooms);
    
    /*for( int i = 0; i < dim; i++ ){
        for( int j = 0; j < dim; j++ ){
            printf( "%d ", map[i][j]);
        }
        printf("\n");
    }*/
    
}
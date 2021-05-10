#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#ifndef MAP
#define MAP

#define MIN_ROOM_DIMENSION 3
#define MAX_ROOM_DIMENSION 8
#define ROOM_MIN_DISTANCE 3

struct room{
    int x;
    int y;
    int w;
    int h;
};

void createMap( int **map, int dim );

#endif
//#include "SDL2/include/SDL.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#ifndef TIMER
#define TIMER

class Timer{
public:
    Timer();
    ~Timer();
    int getPassedTime();
    void start();
    void reset();
private:
    int startTime;
    bool started;
};

#endif
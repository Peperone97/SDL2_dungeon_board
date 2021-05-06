#include <SDL2/SDL.h>

#ifndef TIMER
#define TIMER

class Timer{
public:
    Timer();
    ~Timer();
    int getPassedTime();
private:
    int startTime;
};

#endif
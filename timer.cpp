#include "timer.h"

Timer::Timer(){
    startTime = 0;
    started = false;
    //printf("%d\n", startTime);
}

void Timer::start(){
    if( !started ){
        started = true;
        startTime = SDL_GetTicks();
    }
}

int Timer::getPassedTime(){
    //printf("%d\n", SDL_GetTicks() - startTime);
    return (SDL_GetTicks() / startTime);
}

Timer::~Timer(){}
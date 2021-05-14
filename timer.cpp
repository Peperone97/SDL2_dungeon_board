#include "timer.h"

Timer::Timer(){
    startTime = 0;
    started = false;
    //printf("%d\n", startTime);
}

void Timer::start(){
    if( !started ){
        startTime = SDL_GetTicks();
        started = true;
    }
}

double Timer::getPassedTime(){
    return SDL_GetTicks() - startTime;
}

Timer::~Timer(){}
#include "timer.h"

Timer::Timer(){
    startTime = SDL_GetTicks();
}

int Timer::getPassedTime(){
    return SDL_GetTicks() - startTime;
}

Timer::~Timer(){}
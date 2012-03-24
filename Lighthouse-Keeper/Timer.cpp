#include "Timer.h"
#include "SDL.h"

Timer::~Timer(void) {
}

Timer::Timer() {
	this->startTicks = 0;
	this->started = false;
}

void Timer::start() {
	started = true;
	startTicks = SDL_GetTicks();
}

void Timer::stop() {
	started = false;
}

int Timer::getTicks() {
	
	if (started == true) {
		return SDL_GetTicks() - startTicks;
	} 
	
	return 0;
}

bool Timer::isStarted() {
	return started;
}
#include "Timer.h"



Timer::Timer(Time zaciatocnyCas)
{
	reset();
	add(zaciatocnyCas);
}


Timer::~Timer()
{
}

Time Timer::add(Time paCas) {
	akt_cas += paCas;
	if (stav == STOPNUTY) stav = POZASTAVENY;
	return getElapsedTime();
}

Time Timer::reset(bool paStart) {
	Time time = getElapsedTime();
	akt_cas = Time::Zero;
	stav = STOPNUTY;
	if (paStart) resume();
	return time;
}

Time Timer::pause() {
	if (Getbeziaci()) {
		stav = POZASTAVENY;
		akt_cas += clock.getElapsedTime();
	}
	return getElapsedTime();
}

Time Timer::resume() {
	if (!Getbeziaci()) {
		stav = BEZIACI;
		clock.restart();
	}
	return getElapsedTime();
}

Time Timer::toggle() {
	if (Getbeziaci()) {
		pause();
	}
	else resume();
	return getElapsedTime();
}

bool Timer::Getbeziaci() const
{
	return stav == BEZIACI;
}

Time Timer::getElapsedTime() const
{
	switch (stav) {
	case STOPNUTY:
		return Time::Zero;
	case BEZIACI:
		return akt_cas + clock.getElapsedTime();
	case POZASTAVENY:
		return akt_cas;
	default:
		return akt_cas;
	}
}

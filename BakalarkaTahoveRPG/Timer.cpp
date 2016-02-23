#include "Timer.h"



Timer::Timer(sf::Time zaciatocnyCas)
{
	reset();
	add(zaciatocnyCas);
}


Timer::~Timer()
{
}

sf::Time Timer::add(sf::Time paCas) {
	akt_cas += paCas;
	if (stav == STOPNUTY) stav = POZASTAVENY;
	return getElapsedTime();
}

sf::Time Timer::reset(bool paStart) {
	sf::Time time = getElapsedTime();
	akt_cas = sf::Time::Zero;
	stav = STOPNUTY;
	if (paStart) resume();
	return time;
}

sf::Time Timer::pause() {
	if (Getbeziaci()) {
		stav = POZASTAVENY;
		akt_cas += clock.getElapsedTime();
	}
	return getElapsedTime();
}

sf::Time Timer::resume() {
	if (!Getbeziaci()) {
		stav = BEZIACI;
		clock.restart();
	}
	return getElapsedTime();
}

sf::Time Timer::toggle() {
	if (Getbeziaci()) {
		pause();
	}
	else resume();
	return getElapsedTime();
}

bool Timer::Getbeziaci() {
	return stav == BEZIACI;
}

sf::Time Timer::getElapsedTime() {
	switch (stav) {
	case STOPNUTY:
		return sf::Time::Zero;
	case BEZIACI:
		return akt_cas + clock.getElapsedTime();
	case POZASTAVENY:
		return akt_cas;
	default:
		return akt_cas;
	}
}
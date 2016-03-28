#if !defined(timer_h)
#define timer_h

#include <SFML/System/Clock.hpp>

using namespace sf;

class Timer{
public:
	Timer(Time zaciatocnyCas = Time::Zero);
	~Timer();

	Time add(Time paCas);
	Time reset(bool paStart = false);
	Time pause();
	Time resume();
	Time toggle();
	bool Getbeziaci() const;
	Time getElapsedTime() const;

private:
	enum { STOPNUTY, BEZIACI, POZASTAVENY } stav;
	Time akt_cas;                         
	Clock clock;                 
};
#endif
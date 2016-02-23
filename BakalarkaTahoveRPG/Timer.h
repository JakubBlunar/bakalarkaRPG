#if !defined(timer_h)
#define timer_h

#include <SFML/System/Clock.hpp>

class Timer{
public:
	Timer(sf::Time zaciatocnyCas = sf::Time::Zero);
	~Timer();

	sf::Time add(sf::Time paCas);
	sf::Time reset(bool paStart = false);
	sf::Time pause();
	sf::Time resume();
	sf::Time toggle();
	bool Getbeziaci();
	sf::Time getElapsedTime();

private:
	enum { STOPNUTY, BEZIACI, POZASTAVENY } stav;
	sf::Time akt_cas;                         
	sf::Clock clock;                 
};
#endif
#if !defined(timer_h)
#define timer_h

#include <SFML/System/Clock.hpp>

using namespace sf;

/// <summary>
/// Timer su stopky
/// </summary>
class Timer{
public:
	/// <summary>
	/// Vytvori timer ak nie je nastaveny cas nastavi ho na 0
	/// </summary>
	/// <param name="zaciatocnyCas"></param>
	Timer(Time zaciatocnyCas = Time::Zero);
	~Timer();

	/// <summary>
	/// Propocita k aktualnemu casu iný cas
	/// </summary>
	/// <param name="paCas">Cas kolko pripocitat</param>
	/// <returns>pripocitany cas</returns>
	Time add(Time paCas);

	/// <summary>
	/// Nastavi cas na 0 
	/// </summary>
	/// <param name="paStart">ci sa ma hned spustit alebo byt pozastaveny</param>
	/// <returns>aktualny cas</returns>
	Time reset(bool paStart = false);
	
	/// <summary>
	/// Pozastavi casovac
	/// </summary>
	/// <returns>aktualny</returns>
	Time pause();

	/// <summary>
	/// Obnoví casovac
	/// </summary>
	/// <returns></returns>
	Time resume();

	/// <summary>
	/// Pausne alebo obnovi casovac
	/// </summary>
	/// <returns>aktualny cas</returns>
	Time toggle();

	/// <summary>
	/// Vrati ci stopovanie bezi alebo nie
	/// </summary>
	/// <returns>true ak casovac bezi , false ak nebezi</returns>
	bool Getbeziaci() const;

	/// <summary>
	/// Vrati aktualny cas co je ulozeny v casovaci
	/// </summary>
	/// <returns>aktualny cas</returns>
	Time getElapsedTime() const;

private:
	enum { STOPNUTY, BEZIACI, POZASTAVENY } stav;
	Time akt_cas;                         
	Clock clock;                 
};
#endif
#if !defined(StavInfoHraca_h)
#define StavInfoHraca_h
#include <SFML\Graphics.hpp>
#include "Stav.h"

class Hrac;
class Predmet;
class Akcia;
class Tlacidlo;

/// <summary>
/// Stav ktorý vykresluje Info o hraèovi , èo ma oblecené , aké má štatistiky a kuzla
/// </summary>
class StavInfoHraca : public Stav
{

public:
	StavInfoHraca(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavInfoHraca();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

private:
	/// <summary>
	/// Vykresli okno predmetu nad oznaceny predmet
	/// </summary>
	/// <param name="predmet">predmet ktoreho info zobrazi</param>
	/// <param name="x">pozicia x na ktoru zobrazi</param>
	/// <param name="y">pozicia y na ktoru zobrazi</param>
	/// <param name="okno">okno na ktore sa vykresluje</param>
	void vykresliOknoPredmetu(Predmet*predmet, float x, float y, sf::RenderWindow* okno) const;

	int oznacene;
	sf::RectangleShape ukazovatel;

	Hrac* hrac;
	std::map<int, Predmet*>* oblecene;
	std::vector<Akcia*>* hracoveAkcie;

	std::vector<Tlacidlo*> tlacidlaAkcie;
};

#endif
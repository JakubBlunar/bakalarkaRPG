#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Stav.h"

class Hrac;
class Predmet;
class Akcia;
class Tlacidlo;

class StavInfoHraca : public Stav
{

public:
	StavInfoHraca(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavInfoHraca();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update(double delta) override;

private:
	void vykresliOknoPredmetu(Predmet*predmet, float x, float y, sf::RenderWindow* okno) const;

	int oznacene;
	sf::RectangleShape ukazovatel;

	Hrac* hrac;
	std::map<int, Predmet*>* oblecene;
	std::vector<Akcia*>* hracoveAkcie;

	std::vector<Tlacidlo*> tlacidlaAkcie;
};
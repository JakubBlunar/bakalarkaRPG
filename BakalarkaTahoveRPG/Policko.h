#pragma once
#include "Vrstva.h"
#include <array>

class Hrac;

class Policko
{

public:
	Policko(bool paPriechodne);
	~Policko();

	void hracSkok(Hrac* hrac);
	void interakcia(Hrac* hrac);
	bool jePrechodne();
	void nastavTexturu(sf::Texture textura, int poradie);
	void Setpriechodne(bool paPriechodne);
	sf::Sprite* dajObrazokVrstvy(int poradie);

private:
	//Npc* npc;
	//stack<Predmet> polozenePredmety;
	bool priechodne;
	std::array<Vrstva*, 4> vrstvy;

};
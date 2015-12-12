#pragma once
#include <SFML\Graphics.hpp>
#include <array>

class Hrac;
class Vrstva;

class Policko
{

public:
	Policko(bool paPriechodne);
	virtual ~Policko();

	virtual void hracSkok(Hrac* hrac);
    void interakcia(Hrac* hrac);
	bool jePrechodne();
	void nastavTexturu(sf::Texture* textura, int poradie);
	void Setpriechodne(bool paPriechodne);
	sf::Sprite* dajObrazokVrstvy(int poradie);

protected:
	//Npc* npc;
	//stack<Predmet> polozenePredmety;
	bool priechodne;
	std::array<Vrstva*, 4> vrstvy;
	

};
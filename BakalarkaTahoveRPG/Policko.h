#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <array>

class Hrac;
class Vrstva;
class Npc;
class Predmet;

class Policko
{

public:
	Policko(bool paPriechodne);
	virtual ~Policko();

	virtual void hracSkok(Hrac* hrac);
	void interakcia(Hrac* hrac);
	bool jePrechodne() const;
	void nastavTexturu(sf::Texture* textura, int poradie);
	void Setpriechodne(bool paPriechodne);
	sf::Sprite* dajObrazokVrstvy(int poradie);
	void Setnpc(Npc* paNpc);
	Npc* Getnpc() const;
	void polozPredmet(Predmet* paPredmet,sf::Time kedy);
	std::vector<Predmet*>* dajPolozenePredmety() const;
	bool polozenyPredmet() const;
	void zmazPolozenePredmety();
	float kedyZmazatPredmety() const;

protected:
	Npc* npc;
	std::vector<Predmet*>* polozenePredmety;
	bool priechodne;
	std::array<Vrstva*, 4> vrstvy;
	
	float casMazaniaPredmetov;

};
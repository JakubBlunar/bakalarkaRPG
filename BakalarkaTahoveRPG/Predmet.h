#pragma once

#if !defined(predmet_h)
#define predmet_h

#include <SFML\Graphics.hpp>
#include <string>

class Hrac;

class Predmet
{

public:
	Predmet();
	virtual ~Predmet();

	int Getcena();
	std::string Getmeno();
	sf::Image* Getobrazok();
	void pouzi(Hrac* hrac);
	void Setcena(int newVal);
	void Setmeno(std::string newVal);
	void Setobrazok(sf::Image* newVal);

private:
	int cena;
	std::string meno;
	sf::Image* obrazok;

};
#endif

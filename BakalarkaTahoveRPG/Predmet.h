#pragma once

#if !defined(predmet_h)
#define predmet_h

#include <SFML\Graphics.hpp>
#include <string>

class Hrac;

class Predmet
{

public:
	Predmet(std::string meno, int typ, std::string obrazok, int cena);
	virtual ~Predmet();

	int Getcena();
	int Gettyp();
	std::string Getmeno();
	sf::Sprite* Getobrazok();
	std::string Getstringovytyp();
	void pouzi(Hrac* hrac);
	void Settyp(int newVal);
	void Setcena(int newVal);
	void Setmeno(std::string newVal);
	void Setobrazok(sf::Sprite* newVal);
	

private:
	int typ;
	int cena;
	std::string meno;
	sf::Sprite* obrazok;
	sf::Texture* textura;
	

};
#endif

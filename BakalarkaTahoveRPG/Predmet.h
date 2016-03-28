#pragma once

#if !defined(predmet_h)
#define predmet_h

#include <SFML\Graphics.hpp>

class Hrac;

class Predmet
{

public:
	Predmet(std::string meno, int typ, std::string obrazok, int cena, int paUroven);
	virtual ~Predmet();

	virtual void pouzi(Hrac* hrac);

	int Geturoven() const;
	int Getcena() const;
	int Gettyp() const;
	std::string Getmeno() const;
	sf::Sprite* Getobrazok() const;
	std::string Getstringovytyp() const;
	std::string Getsobrazok() const;
	void Settyp(int newVal);
	void Setcena(int newVal);
	void Setmeno(std::string newVal);
	void Setobrazok(sf::Sprite* newVal);
	virtual Predmet* copy();

protected:
	int uroven;
	int typ;
	int cena;
	std::string meno;
	sf::Sprite* obrazok;
	sf::Texture* textura;
	std::string sObrazok;
	

};
#endif

#pragma once

#if !defined(predmet_h)
#define predmet_h

#include <SFML\Graphics.hpp>

class Hrac;

/// <summary>
/// Zakladná trieda predmet , ktorá predstavuje všetko spoloèné èo maju predmety
/// </summary>
class Predmet
{

public:
	/// <summary>
	/// Vytvori nový zakladný predmet
	/// </summary>
	/// <param name="meno">Nazov Predmetu</param>
	/// <param name="typ">Typ predmetu</param>
	/// <param name="paObrazok">Obrazok predmetu</param>
	/// <param name="cena">Nakupna cena</param>
	/// <param name="paUroven">Potrebna Uroven</param>
	Predmet(std::string meno, int typ, std::string obrazok, int cena, int paUroven);
	virtual ~Predmet();

	/// <summary>
	/// Pouzitie daneho predmetu hracom
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	virtual void pouzi(Hrac* hrac);

	/// <summary>
	/// Vrati potrebnu uroven na pouzitie predmetu
	/// </summary>
	/// <returns>potrebna uroven</returns>
	int Geturoven() const;

	/// <summary>
	/// Vrati cenu predmetu
	/// </summary>
	/// <returns>cena predmetu</returns>
	int Getcena() const;

	/// <summary>
	/// Vrati typ predmetu
	/// </summary>
	/// <returns>typ predmetu</returns>
	int Gettyp() const;

	/// <summary>
	/// Vrati meno predmetu
	/// </summary>
	/// <returns>string meno predmetu</returns>
	std::string Getmeno() const;

	/// <summary>
	/// Vrati obrazok predmetu
	/// </summary>
	/// <returns>Sprite obrazok</returns>
	sf::Sprite* Getobrazok() const;

	/// <summary>
	/// Vrati text popisujuci typ
	/// </summary>
	/// <returns>popis typu</returns>
	std::string Getstringovytyp() const;

	/// <summary>
	/// Vrati nazov suboru z ktoreho bol nacitany obrazok
	/// </summary>
	/// <returns>nazov suboru obrazka</returns>
	std::string Getsobrazok() const;

	/// <summary>
	/// Nastavy typ na zadanu hodnotu
	/// </summary>
	/// <param name="newVal"> nova hodnota</param>
	void Settyp(int newVal);


	/// <summary>
	/// Nastavy cenu na zadanu hodnotu
	/// </summary>
	/// <param name="newVal"> nova hodnota</param>
	void Setcena(int newVal);


	/// <summary>
	/// Nastavy meno na zadanu hodnotu
	/// </summary>
	/// <param name="newVal"> nova hodnota</param>
	void Setmeno(std::string newVal);


	/// <summary>
	/// Nastavy obrazok na zadanu hodnotu
	/// </summary>
	/// <param name="newVal"> nova hodnota</param>
	void Setobrazok(sf::Sprite* newVal);

	/// <summary>
	/// Alokuje v pamäti nový ktorý je kopia a vrati smernik nan
	/// </summary>
	/// <returns>Predmet skopirovaný predmet</returns>
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

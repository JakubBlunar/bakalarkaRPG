#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Trieda predstavuej animaciu, kde je zoznam obrazkov a ona tieto obrazky mení. 
/// </summary>
class Animacia
{

public:
	/// <summary>
	/// Vytvorenie novej animacie
	/// </summary>
	/// <param name="cesta">cesta k obrazku ktorý obsahuje èasti animacie</param>
	/// <param name="pocetObrazkov">pocet obrazkov z ktorých sa sklada animacia</param>
	/// <param name="trvanie">trvanie jedneho obrazka</param>
	/// <param name="velkostX">sirka jedneho obrazka</param>
	/// <param name="velkostY">vyska jedneho obrazka</param>
	Animacia(std::string cesta, int pocetObrazkov, int trvanie, int velkostX,int velkostY);
	virtual ~Animacia();

	/// <summary>
	/// Vráti aktualny obrazok, ktorý je nastaveny v animacii
	/// </summary>
	/// <returns></returns>
	sf::Sprite* dajObrazok() const;

	/// <summary>
	/// Zresetuje animaciu na povodné hodnoty
	/// </summary>
	void reset();
	
	/// <summary>
	/// pripocita k casu trvania snimku urcitu hodnotu a ak treba tak nastavi aktualny obrazok na dalsi
	/// </summary>
	void tick();

	/// <summary>
	/// Vráti sirku obrazka
	/// </summary>
	/// <returns>sirka obrazka</returns>
	int GetvelkostX() const;

	/// <summary>
	/// Vráti výšku obrazka
	/// </summary>
	/// <returns>vyska obrazka</returns>
	int GetvelkostY() const;

private:
	int aktObrazok;
	sf::Texture textura;
	sf::Sprite* obrazok;
	int pocetObrazkov;
	int trvanie;
	int trvanieCounter;
	int velkostTexturyX;
	int velkostTexturyY;


};


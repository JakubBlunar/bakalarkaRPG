#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Trieda predstavuej animaciu, kde je zoznam obrazkov a ona tieto obrazky men�. 
/// </summary>
class Animacia
{

public:
	/// <summary>
	/// Vytvorenie novej animacie
	/// </summary>
	/// <param name="cesta">cesta k obrazku ktor� obsahuje �asti animacie</param>
	/// <param name="pocetObrazkov">pocet obrazkov z ktor�ch sa sklada animacia</param>
	/// <param name="trvanie">trvanie jedneho obrazka</param>
	/// <param name="velkostX">sirka jedneho obrazka</param>
	/// <param name="velkostY">vyska jedneho obrazka</param>
	Animacia(std::string cesta, int pocetObrazkov, int trvanie, int velkostX,int velkostY);
	virtual ~Animacia();

	/// <summary>
	/// Vr�ti aktualny obrazok, ktor� je nastaveny v animacii
	/// </summary>
	/// <returns></returns>
	sf::Sprite* dajObrazok() const;

	/// <summary>
	/// Zresetuje animaciu na povodn� hodnoty
	/// </summary>
	void reset();
	
	/// <summary>
	/// pripocita k casu trvania snimku urcitu hodnotu a ak treba tak nastavi aktualny obrazok na dalsi
	/// </summary>
	void tick();

	/// <summary>
	/// Vr�ti sirku obrazka
	/// </summary>
	/// <returns>sirka obrazka</returns>
	int GetvelkostX() const;

	/// <summary>
	/// Vr�ti v��ku obrazka
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


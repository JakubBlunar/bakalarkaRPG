#pragma once
#include <SFML\Graphics.hpp>

/// <summary>
/// 
/// </summary>
class Vrstva
{

public:
	/// <summary>
	/// vytvori novu vrstvu
	/// </summary>
	/// <param name="velkost">sirka a vyska vrstvy v px</param>
	Vrstva(int velkost);

	/// <summary>
	/// Vytvor� novu vrstvu s texturov na nej
	/// </summary>
	/// <param name="paTextura">textura ktor� sa vlozi do obrazka</param>
	/// <param name="velkost">sirka a vyska vrstvy v px</param>
	Vrstva(sf::Texture paTextura,int paVelkost);
	virtual ~Vrstva();

	/// <summary>
	/// Vrati obrazok vrstvy
	/// </summary>
	/// <returns>obrazok</returns>
	sf::Sprite* Getobrazok() const;

	/// <summary>
	/// nastav� obrazok vrstve
	/// </summary>
	/// <param name="textura">novy obrazok</param>
	void Setobrazok(sf::Texture* textura) const;

private:
	sf::Sprite* obrazok;
	int velkost;

};

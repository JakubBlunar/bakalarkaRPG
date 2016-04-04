#pragma once

#include "SFML\Graphics.hpp"

#include <vector>

using namespace std;

/// <summary>
/// Oblast na mape na ktorej su nejaký nepriatelia
/// </summary>
class Oblast
{
public:
	/// <summary>
	/// Vytvori oblast
	/// </summary>
	/// <param name="paX"> suradnica x zaciatku</param>
	/// <param name="paY">suradnica y zaciatku</param>
	/// <param name="paW">suradnica x konca</param>
	/// <param name="paH">suradnica y konca</param>
	Oblast(int paX, int paY, int paW, int paH);

	/// <summary>
	/// Porovna oblasti , ci su rovnaké
	/// </summary>
	/// <param name="paOblast">druha oblast</param>
	/// <returns>true , false</returns>
	bool jeRovnaka(Oblast paOblast) const;
	
	/// <summary>
	/// Skontroluje ci oblast obsahuje poziciu
	/// </summary>
	/// <param name="paPos">pozicia</param>
	/// <returns>true alebo false</returns>
	bool obsahujeSuradnicu(sf::Vector2i paPos) const;

	/// <summary>
	/// Prida nepriatela na oblast
	/// </summary>
	/// <param name="paMeno">meno suboru v ktorom je ulozeny nepriatel</param>
	void pridajNepriatela(string paMeno);

	/// <summary>
	/// vrati nepriatelov ktorý su na oblasti
	/// </summary>
	/// <returns>zoznam nepriatelov</returns>
	vector<string> Getnepriatelia() const;

	const int x;
	const int y;
	const int w;
	const int h;
private:
	vector<string> nepriatelia;
};


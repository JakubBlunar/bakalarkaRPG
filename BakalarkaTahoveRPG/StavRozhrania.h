#pragma once
#include <map>

#include "Stav.h"

/// <summary>
/// Trieda ktorá organizuje stavy rozhrania, meni ich , su tu ulozené.
/// </summary>
class StavRozhrania
{

public:
	/// <summary>
	/// Vytvorí Manazera rozhraní a priradí mu aktualny stav rozhrania
	/// </summary>
	/// <param name="pociatocnyStav">Stav ktorý sa nastaví ako aktualny</param>
	StavRozhrania(Stav* pociatocnyStav);
	~StavRozhrania();

	/// <summary>
	/// Vykresli aktualny stav
	/// </summary>
	void render() const;

	/// <summary>
	/// Aktualizuje aktualny stav
	/// </summary>
	void update();

	/// <summary>
	/// Pridá nový stav do zoznamu stavov
	/// </summary>
	/// <param name="stav">nový stav</param>
	void pridajStav(Stav* stav);

	/// <summary>
	/// Vráti aktualny stav
	/// </summary>
	/// <returns>stav ktorý ktorý sa vykresluje</returns>
	Stav* GetaktualnyStav() const;

	/// <summary>
	/// Zmeni aktualny stav na stav zadaný parametrom
	/// </summary>
	/// <param name="stav">nazov stavu</param>
	void zmenStav(std::string stav);

	/// <summary>
	/// Vráti stav zo zadaným menom
	/// </summary>
	/// <param name="stav">nazov stavu</param>
	/// <returns>najdený stav alebo nullptr</returns>
	Stav* dajStav(std::string stav);

private:
	std::map<std::string, Stav*> stavy;
	Stav* aktualnyStav;
	Stav* nasledujuci;
};

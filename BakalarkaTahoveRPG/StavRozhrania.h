#pragma once
#include <map>

#include "Stav.h"

/// <summary>
/// Trieda ktor� organizuje stavy rozhrania, meni ich , su tu ulozen�.
/// </summary>
class StavRozhrania
{

public:
	/// <summary>
	/// Vytvor� Manazera rozhran� a prirad� mu aktualny stav rozhrania
	/// </summary>
	/// <param name="pociatocnyStav">Stav ktor� sa nastav� ako aktualny</param>
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
	/// Prid� nov� stav do zoznamu stavov
	/// </summary>
	/// <param name="stav">nov� stav</param>
	void pridajStav(Stav* stav);

	/// <summary>
	/// Vr�ti aktualny stav
	/// </summary>
	/// <returns>stav ktor� ktor� sa vykresluje</returns>
	Stav* GetaktualnyStav() const;

	/// <summary>
	/// Zmeni aktualny stav na stav zadan� parametrom
	/// </summary>
	/// <param name="stav">nazov stavu</param>
	void zmenStav(std::string stav);

	/// <summary>
	/// Vr�ti stav zo zadan�m menom
	/// </summary>
	/// <param name="stav">nazov stavu</param>
	/// <returns>najden� stav alebo nullptr</returns>
	Stav* dajStav(std::string stav);

private:
	std::map<std::string, Stav*> stavy;
	Stav* aktualnyStav;
	Stav* nasledujuci;
};

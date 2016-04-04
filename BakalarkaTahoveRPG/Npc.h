#pragma once
#if !defined(npc_h)
#define npc_h

#include <SFML\Graphics.hpp>

class Animacia;
class Hrac;
class DialogovyStrom;

/// <summary>
/// Npc je postaviËka , ktor· je na mape a hraË s nou moûe komunikovaù
/// </summary>
class Npc
{

public:
	/// <summary>
	/// VytvorÌ npc s menom a jeho dialogom ako bude vedieù komunikovaù
	/// </summary>
	/// <param name="meno">meno npc</param>
	/// <param name="dialog">dialog s hraËom</param>
	Npc(std::string meno, DialogovyStrom* dialog);
	virtual ~Npc();

	/// <summary>
	/// Vrati meno npc
	/// </summary>
	/// <returns>string meno npc</returns>
	std::string Getmeno() const;

	/// <summary>
	/// Vrati dialog npc s hraËom
	/// </summary>
	/// <returns>dialog</returns>
	DialogovyStrom* Getdialog() const;

	/// <summary>
	/// Vrati obrazok ako vyzer· npc
	/// </summary>
	/// <returns>obrazok npc</returns>
	sf::Sprite* dajObrazok() const;

	/// <summary>
	/// Zacne s hracom dialog
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	virtual void dialog(Hrac* hrac);

	/// <summary>
	/// Nastavi npc animaciu , ako bude vyzerat
	/// </summary>
	/// <param name="animacia">jeho animacia</param>
	void Setanimacia(Animacia* animacia);
private:
	Animacia *animacia;
	DialogovyStrom* dialogStrom;
	std::string meno;

};
#endif
#if !defined(elixir_h)
#define elixir_h


#include <string>
#include "Pouzitelny.h"

/// <summary>
/// Trieda predstavuje elixir, ktor� po pou�iti doplni niektoru z hra�ovej �tatistiky
/// </summary>
class Elixir : public Pouzitelny
{

public:
	/// <summary>
	/// Vytvorenie noveho elixiru
	/// </summary>
	/// <param name="meno">Meno elixiru</param>
	/// <param name="typ">EquipSlot predmetu - elixir ma 12</param>
	/// <param name="paObrazok">Obrazok elixiru</param>
	/// <param name="cena">Nakupna cena</param>
	/// <param name="paUroven">potrebn� uroven na pouzitie</param>
	/// <param name="zvysCo">ak� stat bude upravovat</param>
	/// <param name="paoKolko">o kolko ho uprav�</param>
	Elixir(std::string meno, int typ, std::string paObrazok, int cena, int paUroven, std::string zvysCo, int paoKolko);
	virtual ~Elixir();

	/// <summary>
	/// Pouzitie elixiru hracom
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	void pouzi(Hrac* hrac) override;

	/// <summary>
	/// Vrati info o elixire
	/// </summary>
	/// <returns>string info o elixire</returns>
	std::string dajInfo() const;

	/// <summary>
	/// Alokuje v pam�ti nov� elixir ktor� je kopia a vrati smernik nan
	/// </summary>
	/// <returns>Elixir skopirovan� elixir</returns>
	Elixir* copy() override;

	/// <summary>
	/// vrati ak� stat upravuje
	/// </summary>
	/// <returns>string stat</returns>
	std::string Getstat();

	/// <summary>
	/// vrati o kolko upravuje stat
	/// </summary>
	/// <returns>int o kolko</returns>
	int Getokolko();
private:
	std::string stat;
	int oKolko;
};
#endif
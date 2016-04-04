#if !defined(oblecenie_h)
#define oblecenie_h

#include <string>
#include "Pouzitelny.h"

/// <summary>
/// Oblecenie je istı typ pouzitelneho predmetu , ktorı si hrac moze obliec
/// </summary>
class Oblecenie : public Pouzitelny
{

public:
	/// <summary>
	/// Vytvorí nové oblecenie
	/// </summary>
	/// <param name="meno">Nazov Oblecenia</param>
	/// <param name="typ">Equip slot kde bude ulozene</param>
	/// <param name="paObrazok">Obrazok oblecenia</param>
	/// <param name="cena">Nakupna cena</param>
	/// <param name="paUroven">Potrebna Uroven</param>
	Oblecenie(std::string meno, int typ, std::string paObrazok, int cena, int paUroven);

	/// <summary>
	/// Pouzije dané oblecenie , oblecie ho do statistiky.
	/// </summary>
	/// <param name="hrac">hrac ktorı si oblieka danu vec</param>
	void pouzi(Hrac* hrac) override;

	/// <summary>
	/// Alokuje v pamäti nové oblecenie ktoré je kopia a vrati smernik nan
	/// </summary>
	/// <returns>Oblecenie skopirované oblecenie</returns>
	Oblecenie* copy() override;
};
#endif
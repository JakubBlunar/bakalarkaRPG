#if !defined(oblecenie_h)
#define oblecenie_h

#include <string>
#include "Pouzitelny.h"

/// <summary>
/// Oblecenie je ist� typ pouzitelneho predmetu , ktor� si hrac moze obliec�
/// </summary>
class Oblecenie : public Pouzitelny
{

public:
	/// <summary>
	/// Vytvor� nov� oblecenie
	/// </summary>
	/// <param name="meno">Nazov Oblecenia</param>
	/// <param name="typ">Equip slot kde bude ulozene</param>
	/// <param name="paObrazok">Obrazok oblecenia</param>
	/// <param name="cena">Nakupna cena</param>
	/// <param name="paUroven">Potrebna Uroven</param>
	Oblecenie(std::string meno, int typ, std::string paObrazok, int cena, int paUroven);

	/// <summary>
	/// Pouzije dan� oblecenie , oblecie ho do statistiky.
	/// </summary>
	/// <param name="hrac">hrac ktor� si oblieka danu vec</param>
	void pouzi(Hrac* hrac) override;

	/// <summary>
	/// Alokuje v pam�ti nov� oblecenie ktor� je kopia a vrati smernik nan
	/// </summary>
	/// <returns>Oblecenie skopirovan� oblecenie</returns>
	Oblecenie* copy() override;
};
#endif
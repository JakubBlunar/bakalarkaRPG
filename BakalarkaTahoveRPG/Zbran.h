#if !defined(zbran_h)
#define zbran_h

#include "Pouzitelny.h"

/// <summary>
/// typ zbrane urceny pre generator
/// </summary>
enum ZbranTyp {
ONEHAND_AXE = 0,
ONEHAND_SWORD = 1,
DAGGER = 2,
ONEHAND_MACE = 3,
TWOHAND_MACE = 4,
STAVE = 5,
POLEARM = 6,
TWOHAND_AXE = 7,
TWOHAND_SWORD = 8,
SHIELD = 9
};

/// <summary>
/// Zbran je Predmet ktor˝ si hrac moze obliecù , ma poskodnie , r˝chlost utoku a statistiky
/// </summary>
class Zbran : public Pouzitelny
{

public:

	/// <summary>
	/// Vytvori novu zbran
	/// </summary>
	/// <param name="meno">meno zbrane</param>
	/// <param name="typ">equip slot zbrane</param>
	/// <param name="paObrazok">obrazok zbrane</param>
	/// <param name="cena">nakupna cena zbrane</param>
	/// <param name="paUroven">potrebna uroven</param>
	/// <param name="paMinPoskodenie">minimalne poskodenie</param>
	/// <param name="paMaxPoskodnie">maximalne poskodenie</param>
	/// <param name="rychlostUtoku">rychlost utoku v ms</param>
	Zbran(std::string meno,int typ, std::string paObrazok, int cena, int paUroven,int paMinPoskodenie, int paMaxPoskodnie,int rychlostUtoku);
	virtual ~Zbran();

	/// <summary>
	/// Vrati minimalne poskodeie zbrane
	/// </summary>
	/// <returns>int minimalne poskodenie</returns>
	int Getminposkodenie() const;

	/// <summary>
	/// Vrati maximalne poskodenie zbrane
	/// </summary>
	/// <returns>maximalne poskodenie</returns>
	int Getmaxposkodenie() const;

	/// <summary>
	/// Vrati r˝chlost utoku
	/// </summary>
	/// <returns>rychlost utoku v ms</returns>
	int GetrychlostUtoku() const;

	/// <summary>
	/// Oblecie danu zbran hracovi
	/// </summary>
	/// <param name="hrac">Hrac ktor˝ si oblecie danu zbran</param>
	void pouzi(Hrac* hrac) override;

	/// <summary>
	/// Alokuje v pam‰ti nov˙ zbram ktor· je kopia a vrati smernik nanu
	/// </summary>
	/// <returns>Zbran skopirovan· zbran</returns>
	Zbran* copy() override;
private:
	int rychlostUtoku;
	int minPoskodenie;
	int maxPoskodenie;

};
#endif
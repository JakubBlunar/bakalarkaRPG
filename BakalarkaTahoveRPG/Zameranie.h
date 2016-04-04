#if !defined(Zameranie_h)
#define Zameranie_h

#include <map>

class Akcia;

/// <summary>
/// Zameranie je hracove zameranie , ktorÈ udava jeho pocet hp , many,rychlosti a akÈ kuzla bude maù 
/// </summary>
class Zameranie
{

public:
	/// <summary>
	/// VytvorÌ nove zameranie
	/// </summary>
	/// <param name="nazov">Nazov zamerania</param>
	/// <param name="paRastHp">zakladn· hodnota z ktorej je poËitany hracov zivot</param>
	/// <param name="paRastMp">zakladn· hodnota z ktorej je poËitana maximalna mana</param>
	/// <param name="paRastSila">zakladn· hodnota z ktorej je poËitana sila</param>
	/// <param name="paRastRychlost">zakladn· hodnota z ktorej je poËitana rychlost</param>
	/// <param name="paRastIntel">zakladn· hodnota z ktorej je poËitany intelekt</param>
	Zameranie(std::string nazov, int paRastHp, int paRastMp, int paRastSila, int paRastRychlost, int paRastIntel);
	virtual ~Zameranie();

	/// <summary>
	/// Vrati nazov zamerania
	/// </summary>
	/// <returns>string nazov</returns>
	std::string Getnazov() const;

	/// <summary>
	/// Vrati potrebne mnozstvo skusenosti na zadany level
	/// </summary>
	/// <param name="level"> uroven</param>
	/// <returns>int pocet skusenosti</returns>
	int xpNaLevel(int level) const;

	/// <summary>
	/// Vlozi akciu ktoru bude moct vykonavat hrac na danej urovni
	/// </summary>
	/// <param name="paAkcia">akcia</param>
	/// <param name="paUroven">potrebna uroven</param>
	void vlozAkciu(Akcia* paAkcia, int paUroven) const;

	/// <summary>
	/// Vrati bonusy co ziska hrac ked dostane uroven
	/// </summary>
	/// <param name="lvl">uroven</param>
	/// <returns>zoznam bonusov</returns>
	std::map<std::string, int> lvlUpBonusy(int lvl) const;

	/// <summary>
	/// Vrati spelly zamerania
	/// </summary>
	/// <returns>zoznam spellov s ich potrebnou urovnou</returns>
	std::map<Akcia*, int>*  Getspelly() const;

private:
	std::string nazov;
	int rastHp;
	int rastMp;
	int rastIntel;
	int rastRychlost;
	int rastSila;
	std::map<Akcia*, int>*  spelly;

	/// <summary>
	/// Funkcia pomocou ktorej sa pocitaju statistiky
	/// </summary>
	/// <param name="lvl">uroven</param>
	/// <param name="zaklad">zakladna hodnota statistiky</param>
	/// <returns>vypocitana hodnota aku bude mat statistika</returns>
	int statFunkcia(int lvl,int zaklad) const;
};

#endif
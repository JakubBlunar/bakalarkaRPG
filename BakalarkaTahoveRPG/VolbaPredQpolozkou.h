#if !defined(VolbaPredQpolozkou_h)
#define VolbaPredQpolozkou_h

#include "DialogovyStrom.h"
#include "Quest.h"
#include <map>

class Hrac;

/// <summary>
/// Volba, ktorá je pred quest polozkou, zobrazuje text podla stavu questu polozky ktorá je nasledujuca
/// </summary>
class VolbaPredQpolozkou :public DialogVolba
{
public:
	/// <summary>
	/// vytvorí polozku
	/// </summary>
	/// <param name="dalsia">index quest polozky</param>
	/// <param name="paQuest">quest podla ktorého bude zobrazova text</param>
	VolbaPredQpolozkou(int dalsia, Quest* paQuest);

	/// <summary>
	/// Vrati text volby podla stavu questu
	/// </summary>
	/// <returns>string text volby</returns>
	std::string Gettext() override;

	/// <summary>
	/// Pre stav questu priradí urèitı text
	/// </summary>
	/// <param name="paStav">stav questu</param>
	/// <param name="paText">text ktorı bude pri danom stave zobrazenı</param>
	void vlozText(StavQuestu paStav, std::string paText);

private:
	Quest* quest;
	std::map<StavQuestu, std::string> texty;
};

#endif
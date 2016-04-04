#if !defined(VolbaPredQpolozkou_h)
#define VolbaPredQpolozkou_h

#include "DialogovyStrom.h"
#include "Quest.h"
#include <map>

class Hrac;

/// <summary>
/// Volba, ktor� je pred quest polozkou, zobrazuje text podla stavu questu polozky ktor� je nasledujuca
/// </summary>
class VolbaPredQpolozkou :public DialogVolba
{
public:
	/// <summary>
	/// vytvor� polozku
	/// </summary>
	/// <param name="dalsia">index quest polozky</param>
	/// <param name="paQuest">quest podla ktor�ho bude zobrazova� text</param>
	VolbaPredQpolozkou(int dalsia, Quest* paQuest);

	/// <summary>
	/// Vrati text volby podla stavu questu
	/// </summary>
	/// <returns>string text volby</returns>
	std::string Gettext() override;

	/// <summary>
	/// Pre stav questu prirad� ur�it� text
	/// </summary>
	/// <param name="paStav">stav questu</param>
	/// <param name="paText">text ktor� bude pri danom stave zobrazen�</param>
	void vlozText(StavQuestu paStav, std::string paText);

private:
	Quest* quest;
	std::map<StavQuestu, std::string> texty;
};

#endif
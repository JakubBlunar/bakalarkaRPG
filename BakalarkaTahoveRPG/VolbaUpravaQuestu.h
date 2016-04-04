#if !defined(VolbaUpravaQuestu_h)
#define VolbaUpravaQuestu_h

#include "DialogovyStrom.h"
#include "Quest.h"
#include <map>

class Hrac;

/// <summary>
/// Volba ktor� je v quest polozke a stav questu
/// </summary>
class VolbaUpravaQuestu:public DialogVolba 
{
public:
	/// <summary>
	/// Vytvori Volbu ktor� upravuje quest
	/// </summary>
	/// <param name="dalsia">index nasledujucej polozky v zoznane poloziek</param>
	/// <param name="paQuest">quest ktor� sa bude upravova�</param>
	VolbaUpravaQuestu(int dalsia,Quest* paQuest);

	/// <summary>
	/// Skontroluje stav questu a podla neho nieco sprav�, dokonci , prida alebo nic nesprav�.
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	void akcia(Hrac* hrac) override;

	/// <summary>
	/// vrati text podla stavu questu
	/// </summary>
	/// <returns>string text podla questu</returns>
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
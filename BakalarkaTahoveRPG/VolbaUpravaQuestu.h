#if !defined(VolbaUpravaQuestu_h)
#define VolbaUpravaQuestu_h

#include "DialogovyStrom.h"
#include "Quest.h"
#include <map>

class Hrac;

/// <summary>
/// Volba ktorá je v quest polozke a stav questu
/// </summary>
class VolbaUpravaQuestu:public DialogVolba 
{
public:
	/// <summary>
	/// Vytvori Volbu ktorá upravuje quest
	/// </summary>
	/// <param name="dalsia">index nasledujucej polozky v zoznane poloziek</param>
	/// <param name="paQuest">quest ktorı sa bude upravova</param>
	VolbaUpravaQuestu(int dalsia,Quest* paQuest);

	/// <summary>
	/// Skontroluje stav questu a podla neho nieco spraví, dokonci , prida alebo nic nespraví.
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	void akcia(Hrac* hrac) override;

	/// <summary>
	/// vrati text podla stavu questu
	/// </summary>
	/// <returns>string text podla questu</returns>
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
#if !defined(VolbaObchodovanie_h)
#define VolbaObchodovanie_h

#include "DialogovyStrom.h"

class Hrac;

/// <summary>
/// Volba , po ktorej sa ako akcia vykoná otvorenie obchodu
/// </summary>
class VolbaObchodovanie :public DialogVolba
{
public:
	/// <summary>
	/// vytvori novu volbu
	/// </summary>
	/// <param name="paText">text volby</param>
	/// <param name="dalsia">index nasledujucej polozky v zozname poloziek</param>
	/// <param name="akyObchod">json subor v ktorom su ulozene predmety, ktoré npc predáva</param>
	VolbaObchodovanie(string paText, int dalsia,std::string akyObchod);

	/// <summary>
	/// Nacianie obchodu a zobrazenie ho hracovi
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	void akcia(Hrac* hrac) override;
private:
	std::string obchod;
};

#endif
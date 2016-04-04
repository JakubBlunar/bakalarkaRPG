#if !defined(VolbaVyliecenie_h)
#define VolbaVyliecenie_h

#include "DialogovyStrom.h"

class Hrac;

/// <summary>
/// Volba ktorej akcia doplni hracov zivot a manu
/// </summary>
class VolbaVyliecenie :public DialogVolba
{
public:
	/// <summary>
	/// vytvorí novu volbu
	/// </summary>
	/// <param name="paText">text volby</param>
	/// <param name="dalsia">index nasledujucej polozky</param>
	VolbaVyliecenie(string paText, int dalsia);

	/// <summary>
	/// akcia pri ktorej sa doplnia hracova mana a hp
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	void akcia(Hrac* hrac) override;
};

#endif
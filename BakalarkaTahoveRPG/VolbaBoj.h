#if !defined(VolbaBoj_h)
#define VolbaBoj_h

#include <string>

#include "DialogovyStrom.h"

using namespace std;

/// <summary>
/// Volba boj predstavuje polozku pri ktorej sa spusti boj s danym nepriatelom
/// </summary>
class VolbaBoj :
	public DialogVolba
{
public:
	/// <summary>
	/// vytvor� novu volbu
	/// </summary>
	/// <param name="paText">text volby, ktor� uvid� hra�</param>
	/// <param name="dalsia">index nasledujucej polozky</param>
	/// <param name="paNepriatel">subor s menom nepriatela ktor� sa spust� pri vybrati volby</param>
	VolbaBoj(string paText, int dalsia, string paNepriatel);
	virtual ~VolbaBoj();

	/// <summary>
	/// Akcia ktor� sa vykona pri vybrat� volby. Spust� boj s dan�m nepriatelom.
	/// </summary>
	/// <param name="hrac"></param>
	void akcia(Hrac* hrac) override;
private:
	bool pouzita;
	string nepriatel;
};
#endif

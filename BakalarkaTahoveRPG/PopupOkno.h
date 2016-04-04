#if !defined(PopupOkno_h)
#define PopupOkno_h

#include <queue>

using namespace std;

/// <summary>
/// Popupokno je oznamenie ktor� sa hracovi zobraz�
/// </summary>
class PopupOkno
{
public:
	/// <summary>
	/// Vytvor� jednoduch� okno s jednou stranou
	/// </summary>
	/// <param name="paText">text ktor� sa zobrazi</param>
	PopupOkno(string paText);
	~PopupOkno();

	/// <summary>
	/// Prida oknu dalsiu stranku s textom
	/// </summary>
	/// <param name="text">text novej strany</param>
	void pridajStranku(string text);

	/// <summary>
	/// Vrati text aktualnej strany
	/// </summary>
	/// <returns>text </returns>
	string aktualnaStrana();

	/// <summary>
	/// Nastavi stranku na nasledujucu a vrati jej text
	/// </summary>
	/// <returns>text strany</returns>
	string dajDalsi();

	/// <summary>
	/// Vrati ci popup ma este dalsie strany alebo nie
	/// </summary>
	/// <returns>true ak nem� a skoncil , false ak m� a neskoncil</returns>
	bool skoncil() const;
private:
	queue<string> texty;
	bool koniec;
};
#endif


#if !defined(inventar_h)
#define inventar_h

#include "Predmet.h"

/// <summary>
/// Trieda predstavuje hracov inventar kde ma ulozene veci 
/// </summary>
class Inventar
{

public:
	/// <summary>
	/// Vytvori nový inventar o zadanej kapacite a bez veci
	/// </summary>
	/// <param name="kapacita"></param>
	Inventar(int kapacita = 36);

	/// <summary>
	/// Vrati pocet zlata ktoré má hráè
	/// </summary>
	/// <returns>int pocet zlata</returns>
	int Getzlato() const;

	/// <summary>
	/// Nastavi pocet zlata na zadanu hodnotu
	/// </summary>
	/// <param name="paPocet">novy pocet</param>
	void Setzlato(int paPocet);

	/// <summary>
	/// Prida k aktualnemu mnozstvu zlata pocet
	/// </summary>
	/// <param name="paPocet">pocet na pridanie</param>
	void pridajZlato(int paPocet);

	/// <summary>
	/// Metoda ktorá skontroluje èi hraè ma urèite mnozstvo zlata
	/// </summary>
	/// <param name="aktualneZlato">kontrolovane mnozstvo</param>
	/// <returns>true - hrac má , false hrac nemá</returns>
	bool maDostatokZlata(int aktualneZlato) const;
	
	/// <summary>
	/// Vrati kapacitu inventara
	/// </summary>
	/// <returns>int kapacita inventara</returns>
	int Getkapacita() const;

	/// <summary>
	/// Nastavi kapacitu na urcitu hodnotu
	/// </summary>
	/// <param name="paNova">nova kapacita</param>
	void Setkapacita(int paNova);

	/// <summary>
	/// Vrati pocet predmetov z daným menom
	/// </summary>
	/// <param name="meno">meno predmetu</param>
	/// <returns>pocet najdených predmetov</returns>
	int pocetPredmetov(std::string meno);

	/// <summary>
	/// Vrati celkový pocet predmetov ktoré su v inventary
	/// </summary>
	/// <returns>int celkový pocet predmetov</returns>
	int pocetPredmetov() const;

	/// <summary>
	/// Prida predmet do inventara
	/// </summary>
	/// <param name="predmet">Predmet na pridanie</param>
	/// <param name="loot">ci ho hrac lootol alebo nie</param>
	void pridajPredmet(Predmet* predmet,bool loot = true);

	/// <summary>
	/// Zmaze predmet z inventara
	/// </summary>
	/// <param name="predmet">predmet na zmazanie</param>
	void zmazPredmet(Predmet* predmet);

	/// <summary>
	/// Zmaze z inventara všetky predmety z daným menom.
	/// </summary>
	/// <param name="paNazovPredmetu"></param>
	void zmazPredmet(std::string paNazovPredmetu);

	/// <summary>
	/// Vrati predmet na indexe i
	/// </summary>
	/// <param name="i"> index z ktorého predmet sa vráti</param>
	/// <returns>vrátený predmet</returns>
	Predmet* dajPredmetNaIndexe(int i);

private:
	int kapacita;
	int pocetZlata;
	std::vector<Predmet*> predmety;

};
#endif 

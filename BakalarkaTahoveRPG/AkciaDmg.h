#if !defined(akciadmg_h)
#define akciadmg_h

#include "Akcia.h"

/// <summary>
/// Akcia ktorá udeli poskodenie nepriatelovi
/// </summary>
class AkciaDmg : public Akcia
{
public:
	/// <summary>
	/// Konstruktor ktorı vytvorí akciu
	/// </summary>
	/// <param name="meno">nazov Akcie</param>
	/// <param name="obrazok">nazov suboru obrazku akcie</param>
	/// <param name="casCastenia">cas za ktorı sa vykoná akcia od vybratia hracom alebo npc</param>
	/// <param name="cooldown">cas za ktorı sa bude moc opät vybra táto akcia po vykonani</param>
	/// <param name="trvanie">trvanie akcie, spojené s efektom</param>
	/// <param name="popis">popis akcie</param>
	/// <param name="mana">cena many</param>
	/// <param name="typ">typ akcie , ci je magicka alebo fyzicka</param>
	/// <param name="paZakladnyDmg">koeficient zakladneho poskodenia</param>
	AkciaDmg(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana,AkciaTyp typ,double paZakladnyDmg);

	~AkciaDmg();
	
	/// <summary>
	/// Vykonanie akcie, aplikuje poskodenie statistiky1 na statistiku 2
	/// </summary>
	/// <param name="statistika1">statistika z ktorej je pocitane poskodenie</param>
	/// <param name="statistika2">statistika na ktoru sa aplikuje poskodenie</param>
	/// <param name="aktCas">aktualny cas v boji.</param>
	/// <returns>string popisujuci vykonanie akcie</returns>
	std::string vykonajSa(Statistika* statistika1, Statistika* statistika2, sf::Time aktCas) override;
	
	/// <summary>
	/// Funkcia ktorá vypocita zakladné minimalne poskodenie z danej statistiky.
	/// </summary>
	/// <param name="stat">statistika , z ktorej sa vypocíta</param>
	/// <returns>int vysledné vypocitané min poskodenie</returns>
	int minPoskodenie(Statistika* stat) const;

	/// <summary>
	/// Funkcia ktorá vypocita zakladné maximalne poskodenie z danej statistiky.
	/// </summary>
	/// <param name="stat">statistika , z ktorej sa vypocíta</param>
	/// <returns>int vysledné vypocitané max poskodenie</returns>
	int maxPoskodenie(Statistika* stat) const;

private:
	double zakladnyDmg;
};

#endif
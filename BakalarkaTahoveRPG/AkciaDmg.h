#if !defined(akciadmg_h)
#define akciadmg_h

#include "Akcia.h"

/// <summary>
/// Akcia ktor� udeli poskodenie nepriatelovi
/// </summary>
class AkciaDmg : public Akcia
{
public:
	/// <summary>
	/// Konstruktor ktor� vytvor� akciu
	/// </summary>
	/// <param name="meno">nazov Akcie</param>
	/// <param name="obrazok">nazov suboru obrazku akcie</param>
	/// <param name="casCastenia">cas za ktor� sa vykon� akcia od vybratia hracom alebo npc</param>
	/// <param name="cooldown">cas za ktor� sa bude moc op�t vybra� t�to akcia po vykonani</param>
	/// <param name="trvanie">trvanie akcie, spojen� s efektom</param>
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
	/// Funkcia ktor� vypocita zakladn� minimalne poskodenie z danej statistiky.
	/// </summary>
	/// <param name="stat">statistika , z ktorej sa vypoc�ta</param>
	/// <returns>int vysledn� vypocitan� min poskodenie</returns>
	int minPoskodenie(Statistika* stat) const;

	/// <summary>
	/// Funkcia ktor� vypocita zakladn� maximalne poskodenie z danej statistiky.
	/// </summary>
	/// <param name="stat">statistika , z ktorej sa vypoc�ta</param>
	/// <returns>int vysledn� vypocitan� max poskodenie</returns>
	int maxPoskodenie(Statistika* stat) const;

private:
	double zakladnyDmg;
};

#endif
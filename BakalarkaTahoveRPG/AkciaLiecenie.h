#if !defined(akcialiecenie_h)
#define akcialiecenie_h

#include "Akcia.h"

/// <summary>
/// akcia ktor� prid� hp hracovi alebo npc
/// </summary>
class AkciaLiecenie:public Akcia
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
	/// <param name="paZakladnyHeal">koeficient zakladneho liecenia</param>
	AkciaLiecenie(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana, AkciaTyp typ, double paZakladnyHeal);
	
	~AkciaLiecenie();
	
	/// <summary>
	/// Vykonanie akcie, zvysi zivot statistiky1 o hodnotu vypocitanu zo statistiky1
	/// </summary>
	/// <param name="statistika1">statistika z ktorej je pocitane poskodenie</param>
	/// <param name="statistika2">statistika na ktoru sa aplikuje poskodenie</param>
	/// <param name="aktCas">aktualny cas v boji.</param>
	/// <returns>string popisujuci vykonanie akcie</returns>
	std::string vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas) override;

	/// <summary>
	/// Funkcia ktor� vypocita zakladn� minimalne liecenie z danej statistiky.
	/// </summary>
	/// <param name="stat">statistika , z ktorej sa vypoc�ta</param>
	/// <returns>int vysledn� vypocitan� min liecenie</returns>
	int minLiecenie(Statistika* stat) const;

	/// <summary>
	/// Funkcia ktor� vypocita zakladn� maximalne liecenie z danej statistiky.
	/// </summary>
	/// <param name="stat">statistika , z ktorej sa vypoc�ta</param>
	/// <returns>int vysledn� vypocitan� max liecenie</returns>
	int maxLiecenie(Statistika* stat) const;
private:
	double zakladnyHeal;
};

#endif

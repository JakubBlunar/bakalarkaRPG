#if !defined(akciapridanieefektu_h)
#define akciapridanieefektu_h

#include "Akcia.h"

class Efekt;
class Statistika;

/// <summary>
/// Akcia ktor· predstavuje pridanie efektu na nejaku statistiku
/// </summary>
class AkciaPridanieEfektu:public Akcia
{
public:
	/// <summary>
	/// Vyt
	/// </summary>
	/// <param name="meno">nazov Akcie</param>
	/// <param name="obrazok">nazov suboru obrazku akcie</param>
	/// <param name="casCastenia">cas za ktor˝ sa vykon· akcia od vybratia hracom alebo npc</param>
	/// <param name="cooldown">cas za ktor˝ sa bude moc op‰t vybraù t·to akcia po vykonani</param>
	/// <param name="trvanie">trvanie akcie, spojenÈ s efektom</param>
	/// <param name="popis">popis akcie</param>
	/// <param name="mana">cena many</param>
	/// <param name="efekt">Efekt ktor˝ dana akcia bude aplikovat</param>
	/// <param name="naHraca">ci ho aplikuje na toho co ju vykona alebo na protivnika</param>
	AkciaPridanieEfektu(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana,Efekt* efekt, bool naHraca);

	~AkciaPridanieEfektu();
	
	/// <summary>
	/// Vykonanie akcie , aplikovanie konkretneho efektu bud na hraca alebo na nepriatela
	/// </summary>
	/// <param name="statistika1">statistika toho kto ju vyvolal</param>
	/// <param name="statistika2">statistika jeho protivnika</param>
	/// <param name="aktCas">aktualny cas v boji</param>
	/// <returns>string vysledok o vykonani akcie</returns>
	std::string vykonajSa(Statistika* statistika1, Statistika* statistika2, sf::Time aktCas) override;

	/// <summary>
	/// vrati popis akcie , skombinuje popis akcie s popisom efektu
	/// </summary>
	/// <returns>string popis akcie</returns>
	std::string dajPopis() override;

	/// <summary>
	/// Nastavi efektu statistiku , z ktorej si bude pocitaù hodnoty
	/// </summary>
	/// <param name="statistika">statistika, z ktorej sa budu pocitat hodnoty</param>
	void setStatistika(Statistika* statistika) const;
private:
	Efekt* efekt;
	bool hrac;
};

#endif


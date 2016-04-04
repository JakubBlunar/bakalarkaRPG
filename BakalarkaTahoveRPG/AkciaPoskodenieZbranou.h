#if !defined(akciaposkodeniezbranou_h)
#define akciaposkodeniezbranou_h

#include "Akcia.h"
class Statistika;


/// <summary>
/// Akcia ktor� predstavuje utok hracovou zbranou
/// </summary>
class AkciaPoskodenieZbranou:public Akcia
{
public:
	/// <summary>
	/// Vytvorenie akcie
	/// </summary>
	/// <param name="meno">Nazov akcie</param>
	/// <param name="popis">Popis akcie</param>
	/// <param name="paStatistika">Statistika , z ktorej sa vsetko vypocita</param>
	AkciaPoskodenieZbranou(std::string meno,std::string popis,Statistika* paStatistika);
	~AkciaPoskodenieZbranou();
	
	/// <summary>
	/// Vrati rychlost zbrane
	/// </summary>
	/// <returns>int cas ms oblecenej zbrane statistiky</returns>
	int GetcasCastenia() override;

	/// <summary>
	/// vrati vzdy 0, akcia poskodenie zbranov nem� cooldown
	/// </summary>
	/// <returns>int 0</returns>
	int Getcooldown() override;

	/// <summary>
	/// Vrati obrazok akcie
	/// </summary>
	/// <returns>Obrazok predmetu, ktor� je aktualne oblecen�.</returns>
	sf::Sprite* Getobrazok() override;

	/// <summary>
	/// Vrati nazov akcie
	/// </summary>
	/// <returns>string nazov akcie</returns>
	std::string Getmeno() override;

	/// <summary>
	/// Udelenie poskodenia na statistiku 2 vypocitanej zo zbrane ktor� je oblecen� na statistike 1
	/// </summary>
	/// <param name="statistika1">statistika z ktorej sa pocita</param>
	/// <param name="statistika2">statistika , ktorej bude ubrat� zivot</param>
	/// <param name="aktCas">aktualny cas v boji, od zacatia</param>
	/// <returns>string popisujuci vykonanie akcie</returns>
	std::string vykonajSa(Statistika* statistika1, Statistika* statistika2, sf::Time aktCas) override;

	/// <summary>
	/// metoda ktor� vypocita poskodenie
	/// </summary>
	/// <returns>int min poskodenie</returns>
	int minPoskodenie() const;

	/// <summary>
	/// metoda ktor� vypoc�ta max poskodenie
	/// </summary>
	/// <returns>int max poskodenie</returns>
	int maxPoskodenie() const;

private:
	Statistika* statistika;
};

#endif


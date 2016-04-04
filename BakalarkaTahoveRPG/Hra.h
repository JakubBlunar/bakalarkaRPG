#if !defined(Hra_h)
#define Hra_h

#include <SFML/Graphics.hpp>

class Stav;
class Hrac;
class StavRozhrania;
class Loader;

class Hra
{

public:
	Hra();

	/// <summary>
	/// spusti sa hlavna sluèka hry
	/// </summary>
	void start();
	
	/// <summary>
	/// Metoda zmeni stav rozhrania ktorı sa bude vykreslova
	/// </summary>
	/// <param name="paStav">nazov stavu</param>
	void zmenStavRozhrania(std::string paStav) const;

	/// <summary>
	/// Nastavi sa hre hrac
	/// </summary>
	/// <param name="paHrac">hrac</param>
	void Sethrac(Hrac* paHrac);

	/// <summary>
	/// Vrati instanciu hraca ktorı hra hru
	/// </summary>
	/// <returns>hrac</returns>
	Hrac* Gethrac() const;

	/// <summary>
	/// Vrati stav rozhrania ktorı ma zadané meno
	/// </summary>
	/// <param name="stav">nazov stavu</param>
	/// <returns>Stav rozhrania hry</returns>
	Stav* Getstav(std::string stav) const;

	/// <summary>
	/// Vrati èi je okno zakliknuté a otvorené
	/// </summary>
	/// <returns>true ak je , false ak nie je</returns>
	bool maFocus() const;

	/// <summary>
	/// Vrati okno na ktoré sa má vykreslova
	/// </summary>
	/// <returns>Okno hry</returns>
	sf::RenderWindow* Getokno() const;

private:
	Hrac* hrac;
	Loader* loader;
	sf::Clock clock;
	
	/// <summary>
	/// Nastaví premenne na pociatocne hodnoty
	/// </summary>
	void init();

	/// <summary>
	/// Hlavná sluèka programu
	/// </summary>
	void hlavnaSlucka();

	StavRozhrania* stavRozhraniaHry;
	sf::RenderWindow* okno;

	bool focus;

};

#endif

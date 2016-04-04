#if !defined(akcia_h)
#define akcia_h

#include "SFML\Graphics.hpp"

class Statistika;

/// <summary>
/// Enum predstavujuci typ akcie, Ëi je magicka alebo fyzicka
/// </summary>
enum AkciaTyp {
	FYZICKA,
	MAGICKA
};


/// <summary>
/// Z·kladn· trieda akcie, drzi informacie ktorÈ maju akcie spolocnÈ
/// </summary>
class Akcia
{

public:

	/// <summary>
	/// Vytvorenie akcie
	/// </summary>
	/// <param name="meno">nazov Akcie</param>
	/// <param name="obrazok">nazov suboru obrazku akcie</param>
	/// <param name="casCastenia">cas za ktor˝ sa vykon· akcia od vybratia hracom alebo npc</param>
	/// <param name="cooldown">cas za ktor˝ sa bude moc op‰t vybraù t·to akcia po vykonani</param>
	/// <param name="trvanie">trvanie akcie, spojenÈ s efektom</param>
	/// <param name="popis">popis akcie</param>
	/// <param name="mana">cena many</param>
	/// <param name="typ">typ akcie , ci je magicka alebo fyzicka</param>
	Akcia(std::string meno, std::string obrazok, int casCastenia,int cooldown, int trvanie, std::string popis,int mana,AkciaTyp typ);

	/// <summary>
	/// destruktor ktor˝ zmaze alokovanu texturu a obrazok akcie
	/// </summary>
	virtual ~Akcia();

	/// <summary>
	/// metoda ktor· vrati popis akcie
	/// </summary>
	/// <returns>string predstavujuci popis akcie</returns>
	virtual std::string dajPopis();

	/// <summary>
	/// metoda vrati cas castenia akcie
	/// </summary>
	/// <returns>int pocet ms trvania castenia akcie</returns>
	virtual int GetcasCastenia();
	
	/// <summary>
	/// metoda vrati cooldown akcie
	/// </summary>
	/// <returns>int cas coolodwnu v ms</returns>
	virtual int Getcooldown();
	
	/// <summary>
	/// metoda vrati cenu many kolko stoji akcia
	/// </summary>
	/// <returns>int pocet many</returns>
	virtual int Getcenamany();
	
	/// <summary>
	/// metoda vrati meno akcie
	/// </summary>
	/// <returns>string meno akcie</returns>
	virtual std::string Getmeno();
	
	/// <summary>
	/// metoda vrati obrazok akcie
	/// </summary>
	/// <returns>sprite obrazok</returns>
	virtual sf::Sprite* Getobrazok();
	
	/// <summary>
	/// metoda ktora vrati cas trvania akcie
	/// </summary>
	/// <returns>int cas v ms kolko trva akcia</returns>
	int Gettrvanie() const;
	
	/// <summary>
	/// metoda ktor· hracovi znizi manu podla ceny many a vykona sa dana akcia
	/// </summary>
	/// <param name="statHrac">hracova statistika</param>
	/// <param name="statNepriatel">statistika nepriatela</param>
	/// <param name="aktCas">cas trvania boja od zaciatku</param>
	/// <returns>string popis o vykonani akcie</returns>
	virtual std::string vykonajSa(Statistika* statHrac,Statistika* statNepriatel, sf::Time aktCas);

protected:
	AkciaTyp typ;
	int cenaMany;
	int casCastenia;
	int cooldown;
	int trvanie;
	std::string meno;
	std::string popis;
	sf::Sprite* obrazok;
	sf::Texture* textura;
};
#endif

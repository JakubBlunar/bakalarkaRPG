#if !defined(akcia_h)
#define akcia_h
#include "SFML\Graphics.hpp"
#include <string>

class Statistika;

enum AkciaTyp {
	FYZICKA,
	MAGICKA
};

class Akcia
{

public:
	Akcia(std::string meno, std::string obrazok, int casCastenia,int cooldown, int trvanie, std::string popis,int mana,AkciaTyp typ);
	virtual ~Akcia();

	std::string dajPopis();
	virtual int GetcasCastenia();
	virtual int Getcooldown();
	virtual int Getcenamany();
	virtual std::string Getmeno();
	virtual sf::Sprite* Getobrazok();
	int Gettrvanie();
	virtual bool vykonajSa(Statistika* statHrac,Statistika* statNepriatel);

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

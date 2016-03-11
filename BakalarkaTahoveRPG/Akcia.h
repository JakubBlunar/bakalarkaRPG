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

	virtual std::string dajPopis(Statistika* stat);
	virtual int GetcasCastenia();
	virtual int Getcooldown();
	virtual int Getcenamany();
	virtual std::string Getmeno();
	virtual sf::Sprite* Getobrazok();
	int Gettrvanie();
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

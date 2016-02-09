#if !defined(akcia_h)
#define akcia_h
#include "SFML\Graphics.hpp"
#include <string>

class Statistika;
class Akcia
{

public:
	Akcia(std::string meno, std::string obrazok, int casCastenia,int cooldown, int trvanie, std::string popis);
	virtual ~Akcia();

	std::string dajPopis();
	int GetcasCastenia();
	int Getcooldown();
	std::string Getmeno();
	sf::Sprite* Getobrazok();
	int Gettrvanie();
	virtual bool vykonajSa(Statistika* statNeprietel, Statistika* statHrac);

private:
	int casCastenia;
	int cooldown;
	int trvanie;
	std::string meno;
	std::string popis;
	sf::Sprite* obrazok;
	sf::Texture* textura;

};
#endif
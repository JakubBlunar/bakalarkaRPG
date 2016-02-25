#if !defined(akciaposkodeniezbranou_h)
#define akciaposkodeniezbranou_h

#include "Akcia.h"
class Statistika;

class AkciaPoskodenieZbranou:public Akcia
{
public:
	AkciaPoskodenieZbranou(std::string meno,std::string popis,Statistika* paStatistika);
	~AkciaPoskodenieZbranou();
	
	int GetcasCastenia();
	int Getcooldown();
	sf::Sprite* Getobrazok();
	std::string Getmeno();
	std::string vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas);
	int minPoskodenie();
	int maxPoskodenie();

private:
	Statistika* statistika;
};

#endif


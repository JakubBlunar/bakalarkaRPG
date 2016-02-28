#if !defined(akcialiecenie_h)
#define akcialiecenie_h

#include "Akcia.h"
class AkciaLiecenie:public Akcia
{
public:
	AkciaLiecenie(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana, AkciaTyp typ, double paZakladnyHeal);
	~AkciaLiecenie();
	std::string vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas);
	int minLiecenie(Statistika* stat);
	int maxLiecenie(Statistika* stat);
private:
	double zakladnyHeal;
};

#endif

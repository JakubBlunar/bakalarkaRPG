#if !defined(akciadmg_h)
#define akciadmg_h

#include "Akcia.h"

class AkciaDmg : public Akcia
{
public:
	AkciaDmg(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana,AkciaTyp typ,int paZakladnyDmg);
	~AkciaDmg();
	std::string vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas);
	int minPoskodenie(Statistika* stat);
	int maxPoskodenie(Statistika* stat);

private:
	int zakladnyDmg;
};

#endif
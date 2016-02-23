#if !defined(akcialiecenie_h)
#define akcialiecenie_h

#include "Akcia.h"
class AkciaLiecenie:public Akcia
{
public:
	AkciaLiecenie(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana, AkciaTyp typ, int paZakladnyHeal);
	~AkciaLiecenie();
	bool vykonajSa(Statistika* statHrac, Statistika* statNepriatel);
	int minLiecenie(Statistika* stat);
	int maxLiecenie(Statistika* stat);
private:
	int zakladnyHeal;
};

#endif

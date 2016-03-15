#if !defined(akciapridanieefektu_h)
#define akciapridanieefektu_h

#include "Akcia.h"

class Efekt;
class Statistika;

class AkciaPridanieEfektu:public Akcia
{
public:
	AkciaPridanieEfektu(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis, int mana,Efekt* efekt, bool naHraca);
	~AkciaPridanieEfektu();
	std::string vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas);
	std::string dajPopis();
	void setStatistika(Statistika* statistika);
private:
	Efekt* efekt;
	bool hrac;
};

#endif


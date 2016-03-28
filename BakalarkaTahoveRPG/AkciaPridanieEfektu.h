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
	std::string vykonajSa(Statistika* statHrac, Statistika* statNepriatel, sf::Time aktCas) override;
	std::string dajPopis() override;
	void setStatistika(Statistika* statistika) const;
private:
	Efekt* efekt;
	bool hrac;
};

#endif


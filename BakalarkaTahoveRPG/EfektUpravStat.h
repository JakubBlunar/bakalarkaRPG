#if !defined(EfektUpravStat_h)
#define EfektUpravStat_h

#include "Efekt.h"

#include <string>

class Statistika;

class EfektUpravStat :
	public Efekt
{
public:
	EfektUpravStat(std::string obrazok,std::string paCo, int paOkolko);
	~EfektUpravStat();

	void aplikujSa(Statistika* paHrac);
	void zrusUcinok(Statistika* statistika);
	std::string popis(Statistika* statistika);
	int hodnotaEfektu(Statistika* statistika);
private:
	std::string co;
	int zakladOkolko;
};
#endif

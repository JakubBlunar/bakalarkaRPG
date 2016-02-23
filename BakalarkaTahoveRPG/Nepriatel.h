#if !defined(nepriatel_h)
#define nepriatel_h

#include "Statistika.h"
//#include "LogikaNpc.h"
#include "Npc.h"
#include <map>

class Nepriatel : public Npc
{

public:
	Nepriatel(std::string paMeno, DialogovyStrom* dialog, Statistika* paStatistika);
	virtual ~Nepriatel();

	//LogikaNpc Getlogika();
	Statistika* Getstatistika();
	//void Setlogika(LogikaNpc newVal);
	void Setstatistika(Statistika* newVal);
	Akcia* vyberAkciu(std::map<Akcia*,int>* cooldowny);

private:
	//LogikaNpc logika;
	Statistika* statistika;
	

};
#endif

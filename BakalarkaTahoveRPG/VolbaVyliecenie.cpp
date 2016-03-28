#include "VolbaVyliecenie.h"
#include "Hrac.h"
#include "Statistika.h"


VolbaVyliecenie::VolbaVyliecenie(string paText, int dalsia)
	:DialogVolba(paText, dalsia)
{	
}


VolbaVyliecenie::~VolbaVyliecenie()
{
}

void VolbaVyliecenie::akcia(Hrac* hrac) {
	
	hrac->Getstatistika()->Sethp(hrac->Getstatistika()->GethpMax());
	hrac->Getstatistika()->Setmp(hrac->Getstatistika()->GetmpMax());

}

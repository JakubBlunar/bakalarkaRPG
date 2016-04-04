#include "VolbaObchodovanie.h"
#include "Loader.h"
#include "Hra.h"
#include "StavObchod.h"


VolbaObchodovanie::VolbaObchodovanie(string paText, int dalsia,std::string akyObchod):DialogVolba(paText,dalsia)
{
	obchod = akyObchod;
}

void VolbaObchodovanie::akcia(Hrac* hrac) {
	StavObchod* stavObchod = static_cast<StavObchod*>(Loader::Instance()->Gethra()->Getstav("stavObchod"));
	stavObchod->nacitajObchod(obchod);
	Loader::Instance()->Gethra()->zmenStavRozhrania("stavObchod");
}
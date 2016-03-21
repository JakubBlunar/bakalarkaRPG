#include "VolbaBoj.h"
#include "Hra.h"
#include "Loader.h"
#include "StavBoj.h"
#include "Hrac.h"
#include "Boj.h"


VolbaBoj::VolbaBoj(string paText, int dalsia, string paNepriatel)
	:DialogVolba(paText,dalsia)
{
	nepriatel = paNepriatel;
	pouzita = false;
}


VolbaBoj::~VolbaBoj()
{

}


void VolbaBoj::akcia(Hrac* hrac) {
	if (!pouzita) {
		Hra* hra = Loader::Instance()->Gethra();
		Nepriatel* nepriatel = Loader::Instance()->nacitajNepriatela(this->nepriatel);
		StavBoj* stavBoj = (StavBoj*)hra->dajStav("stavBoj");
		stavBoj->setBoj(new Boj(hrac, nepriatel));
		pouzita = true;
		hra->zmenStavRozhrania("stavBoj");
	}
}

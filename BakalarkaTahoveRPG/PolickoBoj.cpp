#include "PolickoBoj.h"
#include "Hrac.h"
#include "Hra.h"
#include <string>
#include "Mapa.h"
#include "StavHranieHry.h"
#include "Loader.h"

#include "StavBoj.h"
#include "Boj.h"
#include "PopupOkno.h"
#include "Nepriatel.h"
#include "AudioManager.h"
#include "Generator.h"

PolickoBoj::PolickoBoj(bool paPriechodne) :Policko(paPriechodne)
{
}


PolickoBoj::~PolickoBoj()
{
	
}

void PolickoBoj::hracSkok(Hrac* paHrac) {

	Hra* hra = Loader::Instance()->Gethra();
	StavHranieHry* stavHranieHry = static_cast<StavHranieHry*>(Loader::Instance()->Gethra()->Getstav("hranieHry"));
	Mapa* mapa = stavHranieHry->getMapa();


	int p = Generator::Instance()->randomInt(0, 99);

	if (p < 15) {

		std::vector<std::string>* moznyNepriatelia = mapa->Getmoznynepriatelia();
		if (moznyNepriatelia->size() > 0) {
			int id = Generator::Instance()->randomInt(0, moznyNepriatelia->size() - 1);
			Nepriatel* nepriatel = Loader::Instance()->nacitajNepriatela(moznyNepriatelia->at(id));
			StavBoj* stavBoj = static_cast<StavBoj*>(hra->Getstav("stavBoj"));
			stavBoj->setBoj(new Boj(paHrac, nepriatel));
			AudioManager::Instance()->playEfekt("start_boja");

			stavHranieHry->zobrazPopup(new PopupOkno(nepriatel->Getmeno() + " level " + std::to_string(nepriatel->Getstatistika()->dajUroven()) + " appeared!."));
			hra->zmenStavRozhrania("stavBoj");
		}
	}


}
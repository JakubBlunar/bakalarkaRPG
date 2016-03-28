#include "PolickoBoj.h"
#include "Hrac.h"
#include "Hra.h"
#include <string>
#include "Mapa.h"
#include "StavHranieHry.h"
#include "Loader.h"
#include <random>

#include "StavBoj.h"
#include "Boj.h"
#include "PopupOkno.h"
#include "Nepriatel.h"

PolickoBoj::PolickoBoj(bool paPriechodne) :Policko(paPriechodne)
{
}


PolickoBoj::~PolickoBoj()
{
	
}

void PolickoBoj::hracSkok(Hrac* paHrac) {

	Hra* hra = Loader::Instance()->Gethra();
	StavHranieHry* stavHranieHry = static_cast<StavHranieHry*>(Loader::Instance()->Gethra()->dajStav("hranieHry"));
	Mapa* mapa = stavHranieHry->getMapa();


	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> real(0, 1);
	double p = real(generator);

	if (0.15 >= p) {

		std::vector<std::string>* moznyNepriatelia = mapa->Getmoznynepriatelia();
		if (moznyNepriatelia->size() > 0) {
			std::uniform_int_distribution<int> rand(0, moznyNepriatelia->size() - 1);
			int id = rand(generator);

			/*

			*/

			Nepriatel* nepriatel = Loader::Instance()->nacitajNepriatela(moznyNepriatelia->at(id));
			StavBoj* stavBoj = static_cast<StavBoj*>(hra->dajStav("stavBoj"));
			stavBoj->setBoj(new Boj(paHrac, nepriatel));

			stavHranieHry->zobrazPopup(new PopupOkno(nepriatel->Getmeno() + " level " + std::to_string(nepriatel->Getstatistika()->dajUroven()) + " appeared!."));
			hra->zmenStavRozhrania("stavBoj");
		}
	}



		


}
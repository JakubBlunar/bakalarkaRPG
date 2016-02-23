#include "PolickoBoj.h"
#include "Hrac.h"
#include "Hra.h"
#include <iostream>
#include <string>
#include "Mapa.h"
#include "StavHranieHry.h"
#include "Loader.h"
#include <random>

#include "Statistika.h"
#include "Akcia.h"
#include "Nepriatel.h"
#include "StavBoj.h"
#include "Boj.h"
#include "PopupOkno.h"
#include "AkciaDmg.h"

PolickoBoj::PolickoBoj(bool paPriechodne) :Policko(paPriechodne)
{
	jePopup = false;
	zapnute = false;
}


PolickoBoj::~PolickoBoj()
{

}

void PolickoBoj::hracSkok(Hrac* paHrac) {

	Hra* hra = Loader::Instance()->Gethra();
	StavHranieHry* stavHranieHry = (StavHranieHry*) Loader::Instance()->Gethra()->dajStav("hranieHry");
	Mapa* mapa = stavHranieHry->getMapa();
	
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> real(0, 1);
	double p = real(generator);

	if (0.1 >= p) {
		Statistika* npcStatistika = new Statistika(1, 60, 80, 40, 50, 2, 6,2,25);
		npcStatistika->vlozAkciu(new AkciaDmg("Poleptanie kyselinou", "attack", 2000, 0, 0, "", 0, AkciaTyp::FYZICKA,1));
		Nepriatel* nepriatel = new Nepriatel("Nejaký sliz", nullptr, npcStatistika);

		StavBoj* stavBoj = (StavBoj*)hra->dajStav("stavBoj");
		stavBoj->setBoj(new Boj(paHrac, nepriatel));

		stavHranieHry->zobrazPopup(new PopupOkno("Napdol ta " + nepriatel->Getmeno()));
		hra->zmenStavRozhrania("stavBoj");
	}



		


}
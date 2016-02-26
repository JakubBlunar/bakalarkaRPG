#include "PolickoBoj.h"
#include "Hrac.h"
#include "Hra.h"
#include <iostream>
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

		std::vector<std::string>* moznyNepriatelia = mapa->Getmoznynepriatelia();

		std::uniform_int_distribution<int> rand(0, moznyNepriatelia->size()-1);
		int id = rand(generator);

		/*
		
		*/
		Nepriatel* nepriatel = Loader::Instance()->nacitajNepriatela(moznyNepriatelia->at(id));
		StavBoj* stavBoj = (StavBoj*)hra->dajStav("stavBoj");
		stavBoj->setBoj(new Boj(paHrac, nepriatel ));

		stavHranieHry->zobrazPopup(new PopupOkno("Napdol ta " + nepriatel->Getmeno()));
		hra->zmenStavRozhrania("stavBoj");
	}



		


}
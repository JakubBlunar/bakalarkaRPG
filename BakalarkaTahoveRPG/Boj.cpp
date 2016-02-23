#include "Boj.h"
#include "Nepriatel.h"
#include "Hrac.h"
#include "Akcia.h"
#include "Loader.h"
#include "Hra.h"
#include "Mapa.h"
#include "StavHranieHry.h"
#include "PopupOkno.h"
#include "Inventar.h"

#include <iostream>

Boj::Boj(Hrac* paHrac, Nepriatel* paNpc) {
	hrac = paHrac;
	npc = paNpc;
	vyber = true;
	hracAkcia = nullptr;
	npcAkcia = nullptr;
	hracCasVykonaniaAkcie = 0;
	npcCasVykonaniaAkcie = 0;
}



Boj::~Boj() {

}

void Boj::bojStart() {
	casovac.reset(true);
	casovac.add(sf::milliseconds(1));
	koniec = false;
	boloVyhodnotenie = false;
}



bool Boj::koniecBoja() {
	return koniec;
}

Statistika* Boj::Gethracovastatistika() {
	return hrac->Getstatistika();
}

Statistika* Boj::Getnpcstatistika() {
	return npc->Getstatistika();
}

bool Boj::cakaNaVybratieAkcie() {
	return vyber;
}

sf::Time Boj::Getcasvboji() {
	return casovac.getElapsedTime();
}

void Boj::hracVybralAkciu(Akcia* paAkcia) {
	vyber = false;
	hracAkcia = paAkcia;
	hracCasVykonaniaAkcie = casovac.getElapsedTime().asMilliseconds() + hracAkcia->GetcasCastenia();
	casovac.resume();
	std::cout << "Vybrata akcia " << paAkcia->Getmeno() << std::endl;
	
}

float Boj::castBarProgres() {
	if (hracAkcia == nullptr) {
		return -1;
	}
	else {
		if (hracAkcia->GetcasCastenia() != 0) {
			return  (float)(casovac.getElapsedTime().asMilliseconds() - (hracCasVykonaniaAkcie - hracAkcia->GetcasCastenia()))/ hracAkcia->GetcasCastenia();
		}
		else return -1;
	}
}

bool Boj::maAkciaCooldown(Akcia* paAkcia) {
	if (!vyber) {
		return true;
	}
	else {
		if (paAkcia->Getcenamany() > hrac->Getstatistika()->Getmp()) {
			return true;
		}
		std::map<Akcia*, int>::iterator it = hracCooldowny.find(paAkcia);
		if (it != hracCooldowny.end())
		{
			return true;
		}
	}
	return false;
}

void Boj::update() {
	if (!koniec) {
		casovac.pause();
		//aktualizuje cooldowny hraca
		for (std::map<Akcia*, int>::iterator it = hracCooldowny.begin(); it != hracCooldowny.end(); ++it)
		{
			if (it->second <= casovac.getElapsedTime().asMilliseconds()) {
				hracCooldowny.erase(it->first);
			}
		}

		//aktualizuje cooldowny npc
		for (std::map<Akcia*, int>::iterator it = npcCooldowny.begin(); it != npcCooldowny.end(); ++it)
		{
			if (it->second <= casovac.getElapsedTime().asMilliseconds()) {
				npcCooldowny.erase(it->first);
			}
		}
		

		if (casovac.getElapsedTime().asMilliseconds() > hracCasVykonaniaAkcie && hracAkcia != nullptr) {

			hracAkcia->vykonajSa(hrac->Getstatistika(), npc->Getstatistika());
			hracCooldowny.insert(std::pair<Akcia*, int>(hracAkcia, casovac.getElapsedTime().asMilliseconds() + hracAkcia->Getcooldown()));
			hracAkcia = nullptr;
		}

		if (casovac.getElapsedTime().asMilliseconds() > npcCasVykonaniaAkcie && npcAkcia != nullptr) {

			npcAkcia->vykonajSa(npc->Getstatistika(), hrac->Getstatistika());
			npcCooldowny.insert(std::pair<Akcia*, int>(npcAkcia, casovac.getElapsedTime().asMilliseconds() + npcAkcia->Getcooldown()));	
			npcAkcia = nullptr;
		}

		if (hrac->Getstatistika()->Gethp() <= 0 || npc->Getstatistika()->Gethp() <= 0 ) {
			koniec = true;
		}
		

		if( npcAkcia == nullptr) {// vyberie si npc akciu
			Akcia* akcia;
			akcia = npc->vyberAkciu(&npcCooldowny);
			npcAkcia = akcia;
			if(akcia != nullptr){
				npcCasVykonaniaAkcie = casovac.getElapsedTime().asMilliseconds() + akcia->GetcasCastenia();
				casovac.resume();
			}
		}


		if (hracAkcia == nullptr) {
			vyber = true;
			casovac.pause();
		}
		else {
			casovac.resume();
		}
	}
	else {
		this->vyhodnotenie();
	}

}

void Boj::vyhodnotenie() {
	if (!boloVyhodnotenie) {
		boloVyhodnotenie = true;

		Hra* hra = Loader::Instance()->Gethra();
		StavHranieHry* stavHranieHry = (StavHranieHry*)Loader::Instance()->Gethra()->dajStav("hranieHry");
		Mapa* mapa = stavHranieHry->getMapa();

		if (hrac->Getstatistika()->Gethp() > 0) {
			std::cout << "Vyhral hrac" << std::endl;
			int ziskaneXp = 1;
			int ziskaneZlato = 10;
			hrac->pridajSkusenosti(ziskaneXp);
			hrac->Getinventar()->pridajZlato(ziskaneZlato);
			std::string text = "Porazil si " + npc->Getmeno() + "\n";
			text += "Ziskal si " + std::to_string(ziskaneXp) + " skusenosti a " + std::to_string(ziskaneZlato) + " zlata";

			stavHranieHry->zobrazPopup(new PopupOkno(text));
			hra->zmenStavRozhrania("hranieHry");
		}
		else {
			std::cout << "Vyhral Npc" << std::endl;
		}

	}
}
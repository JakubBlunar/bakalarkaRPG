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
#include "Efekt.h"
#include "QuestManager.h"
#include "Policko.h"
#include "Generator.h"
#include "Quest.h"

#include <map>
#include <iostream>
#include <random>
#include <deque>



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
	hrac->Getstatistika()->setCombat(true);
	npc->Getstatistika()->setCombat(true);
}

Nepriatel* Boj::Getnepriatel() {
	return npc;
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
}

float Boj::castBarProgres() {
	if (hracAkcia == nullptr) {
		return -1;
	}
	else {
		if (hracAkcia->GetcasCastenia() != 0) {
			return  (float)(casovac.getElapsedTime().asMilliseconds() - (hracCasVykonaniaAkcie - hracAkcia->GetcasCastenia())) / hracAkcia->GetcasCastenia();
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

		//bonusy hraca
		std::map<Efekt*, sf::Time>* aktivneEfekty = hrac->Getstatistika()->Getaktivneefekty();
		for (std::map<Efekt*, sf::Time>::iterator it = aktivneEfekty->begin(); it != aktivneEfekty->end(); ++it)
		{
			if (it->second <= casovac.getElapsedTime()) {
				hrac->Getstatistika()->zrusEfekt(it->first);
				logBoja.push_front("Hrac: zrusenie efektu " + it->first->popis(npc->Getstatistika()));
			}
		}

		//bonusy npc
		aktivneEfekty = npc->Getstatistika()->Getaktivneefekty();

		for (std::map<Efekt*, sf::Time>::iterator it = aktivneEfekty->begin(); it != aktivneEfekty->end(); ++it)
		{
			if (it->second <= casovac.getElapsedTime()) {
				npc->Getstatistika()->zrusEfekt(it->first);
				logBoja.push_front("Npc: zrusenie efektu " + it->first->popis(hrac->Getstatistika()));
			}
		}


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
			std::string vysledok = hracAkcia->vykonajSa(hrac->Getstatistika(), npc->Getstatistika(), casovac.getElapsedTime());
			logBoja.push_front("Hrac: " + vysledok);
			hracCooldowny.insert(std::pair<Akcia*, int>(hracAkcia, casovac.getElapsedTime().asMilliseconds() + hracAkcia->Getcooldown()));
			hracAkcia = nullptr;
		}

		if (casovac.getElapsedTime().asMilliseconds() > npcCasVykonaniaAkcie && npcAkcia != nullptr) {
			std::string vysledok = npcAkcia->vykonajSa(npc->Getstatistika(), hrac->Getstatistika(), casovac.getElapsedTime());
			logBoja.push_front("Npc: " + vysledok);
			npcCooldowny.insert(std::pair<Akcia*, int>(npcAkcia, casovac.getElapsedTime().asMilliseconds() + npcAkcia->Getcooldown()));
			npcAkcia = nullptr;
		}

		if (hrac->Getstatistika()->Gethp() <= 0 || npc->Getstatistika()->Gethp() <= 0) {
			koniec = true;
		}


		if (npcAkcia == nullptr) {// vyberie si npc akciu
			Akcia* akcia;
			akcia = npc->vyberAkciu(&npcCooldowny);
			npcAkcia = akcia;
			if (akcia != nullptr) {
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
			int ziskaneXp = npc->Getstatistika()->dajUroven() - hrac->Getstatistika()->dajUroven();
			if (ziskaneXp < 1) {
				ziskaneXp = 1;
			}

			int ziskaneZlato = 2 * npc->Getstatistika()->dajUroven();
			hrac->pridajSkusenosti(ziskaneXp);
			hrac->Getinventar()->pridajZlato(ziskaneZlato);
			std::string text = "Porazil si " + npc->Getmeno() + "\n";
			text += "Ziskal si " + std::to_string(ziskaneXp) + " skusenosti a " + std::to_string(ziskaneZlato) + " zlata";
			stavHranieHry->zobrazPopup(new PopupOkno(text));
			QuestManager* qm = hrac->Getmanazerquestov();
			qm->udalost(Event::ZABITIE_NPC, npc);

			if (rand() % 100 < 35) {// 35% že padne predmet
				int cislo = rand() % 100;
				int lvlOd = npc->Getstatistika()->dajUroven() - 2;
				int lvlDo = npc->Getstatistika()->dajUroven() + 2;
				if (lvlOd < 1) {
					lvlOd = 1;
				}

				int vyslednyLvl = lvlOd + rand() % (lvlDo - lvlOd + 1);

				if (cislo < 25) {
					mapa->GetPolicko(hrac->GetpolickoX(), hrac->GetpolickoY())->polozPredmet(Generator::Instance()->nahodnaZbran(vyslednyLvl), mapa->aktCas());
				}
				else if (cislo < 50) {
					mapa->GetPolicko(hrac->GetpolickoX(), hrac->GetpolickoY())->polozPredmet(Generator::Instance()->nahodneOblecenie(vyslednyLvl), mapa->aktCas());
				}
				else {
					mapa->GetPolicko(hrac->GetpolickoX(), hrac->GetpolickoY())->polozPredmet(Generator::Instance()->nahodnyElixir(), mapa->aktCas());
				}
			}

			std::deque<Quest*>* nedokonceneQuesty = hrac->Getmanazerquestov()->Getnedokoncenequesty();
			std::map<std::string, Predmet*>* questDrop = npc->dropQuestPredmetov();

			for (unsigned int i = 0; i < nedokonceneQuesty->size(); i++) {
				Quest* q = nedokonceneQuesty->at(i);
				if (questDrop->count(q->Getnazov()) && q->Getstav() == StavQuestu::ROZROBENY) {// predmet je v npc drope a je rozrobeny
					if (rand() % 100 < 40) {
						mapa->GetPolicko(hrac->GetpolickoX(), hrac->GetpolickoY())->polozPredmet(questDrop->at(q->Getnazov())->copy(), mapa->aktCas());
					}
				}
			}


		}
		else {

			Statistika* s = hrac->Getstatistika();
			s->Sethp(s->GethpMax());
			s->Setmp(s->GetmpMax());

			while (hrac->Getinventar()->pocetPredmetov() != 0) {

				Predmet * p = hrac->Getinventar()->dajPredmetNaIndexe(hrac->Getinventar()->pocetPredmetov() - 1);
				hrac->Getinventar()->zmazPredmet(p);
				mapa->GetPolicko(hrac->GetpolickoX(), hrac->GetpolickoY())->polozPredmet(p, mapa->aktCas());
			}

			mapa->posunHracaNaPolicko(mapa->Gethrobsuradnice().x, mapa->Gethrobsuradnice().y, 0);
			stavHranieHry->zobrazPopup(new PopupOkno("Upadol si do bezvedomia ! Zobudil si sa a zistil si ze si stratil všetky veci."));
		}

		//zrusenie aktivnych bufov
		std::map<Efekt*, sf::Time>* aktivneEfekty = hrac->Getstatistika()->Getaktivneefekty();
		for (std::map<Efekt*, sf::Time>::iterator it = aktivneEfekty->begin(); it != aktivneEfekty->end(); ++it)
		{
			hrac->Getstatistika()->zrusEfekt(it->first);
		}

		hrac->Getstatistika()->setCombat(false);
		hra->zmenStavRozhrania("hranieHry");
	}
}

std::string Boj::Getlog(int paOd, int paDo) {
	int indexOd, indexDo;
	if (paOd < 0) {
		indexOd = 0;
	}
	else indexOd = paOd;

	if (paDo >= (signed int)logBoja.size()) {
		indexDo = logBoja.size() - 1;
	}
	else indexDo = paDo;

	std::string log = "";
	for (signed int i = indexOd; i <= indexDo; i++) {
		log += logBoja.at(i) + "\n";
	}
	return log;
}
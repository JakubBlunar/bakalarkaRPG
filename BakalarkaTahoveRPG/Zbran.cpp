#include "Zbran.h"

#include "Hrac.h"
#include "Statistika.h"
#include "Inventar.h"

Zbran::Zbran(std::string meno, int typ, std::string paObrazok, int cena, int paMinPoskodenie, int paMaxPoskodnie) :Pouzitelny(meno, typ, paObrazok, cena) {
	minPoskodenie = paMinPoskodenie;
	maxPoskodenie = paMaxPoskodnie;
}



Zbran::~Zbran() {

}



/*
	hnusn� rie�enie a nepa�i sa mi :D
*/

void Zbran::pouzi(Hrac* hrac) {
	std::map<int, Predmet*>* oblecene = hrac->Getstatistika()->Getoblecene();
	Pouzitelny* docasny1;
	Pouzitelny* docasny2;

	if (!Pouzitelny::Isobleceny()) {
		int typ = Gettyp();

		if (typ == 1) { // je to jednoru�n� zbran
			
			if (oblecene->count(1)) { // u� je zbran na prvom slote

				if (oblecene->count(2)) { // je zbran na druhom slote tak vymen� zbrane v prvom , druhu necha tak
					docasny1 =(Pouzitelny*)oblecene->at(1);
					oblecene->erase(1);
					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
					
					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);
					Pouzitelny::Setobleceny(true);
					
				}
				else {// na slote 2 nie je �iadna zbran
					docasny1 = (Pouzitelny*)oblecene->at(1);
					if (docasny1->Gettyp() != 2) {//na slote 1 nie je obojrucna zbran
						Pouzitelny::Setobleceny(true);
						oblecene->insert(std::pair<int, Predmet*>(2, this));
						hrac->Getinventar()->zmazPredmet(this);
					}
					else { // ak je obojru�na tak mo�e dr�a� len tu , vrati zbran zo slotu 1 do inventu
						oblecene->erase(1);
						docasny1->Setobleceny(false);
						hrac->Getinventar()->pridajPredmet(docasny1);

						Pouzitelny::Setobleceny(true);
						oblecene->insert(std::pair<int, Predmet*>(2, this));
						hrac->Getinventar()->zmazPredmet(this);
					}
				}


			}
			else {// nie je ni� oblecene tak ho oblecie
				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(1, this));
				hrac->Getinventar()->zmazPredmet(this);
			}

		}
		else if (typ == 2) { // je to obojru�na
			if (oblecene->count(1)) {
				if (oblecene->count(2)) {// na slote 2 je nejak� predmet tak ho aj so branou na prvom slote vlozi do inventara

					docasny1 = (Pouzitelny*)oblecene->at(1);
					docasny2 = (Pouzitelny*)oblecene->at(2);

					oblecene->erase(1);
					oblecene->erase(2);

					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
					
					docasny2->Setobleceny(false);
					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);
					hrac->Getinventar()->pridajPredmet(docasny2);

					Pouzitelny::Setobleceny(true);
				}
				else {  // na slote 2 ni� nie je ... iba da zbran do slotu 1 a zbran z 1 do inventu
					docasny1 = (Pouzitelny*)oblecene->at(1);
					oblecene->erase(1);
					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);
					Pouzitelny::Setobleceny(true);

				}

			}
			else {
				if (oblecene->count(2)) {  // na 2. slote je zbran alebo stit tak ju da dole
					docasny1 = (Pouzitelny*)oblecene->at(2);
					oblecene->erase(2);
					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);

					Pouzitelny::Setobleceny(true);
					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
				}
				else {// na druhom slote nie je nic a ani na prvom tak len nasad� zbran
					Pouzitelny::Setobleceny(true);
					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
				}
			}
			

		}
		else {//je to stit

			if (oblecene->count(2)) {// je nieco v 2 slote na zbran
				docasny1 = (Pouzitelny*)oblecene->at(2);
				oblecene->erase(2);
				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);

				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(2, this));
				hrac->Getinventar()->zmazPredmet(this);

			}
			else {
				if (oblecene->count(1)) {
					docasny1 = (Pouzitelny*)oblecene->at(1);
					if (docasny1->Gettyp() == 2) { // ma obojrucnu zbran
						oblecene->erase(1);
						docasny1->Setobleceny(false);
						hrac->Getinventar()->pridajPredmet(docasny1);

						Pouzitelny::Setobleceny(true);
						oblecene->insert(std::pair<int, Predmet*>(2, this));
						hrac->Getinventar()->zmazPredmet(this);
					}
					else {
						Pouzitelny::Setobleceny(true);
						oblecene->insert(std::pair<int, Predmet*>(2, this));
						hrac->Getinventar()->zmazPredmet(this);
					}
				}
				else {
					Pouzitelny::Setobleceny(true);
					oblecene->insert(std::pair<int, Predmet*>(2, this));
					hrac->Getinventar()->zmazPredmet(this);
				}
			}
		}
	
				
	}
	else {

	}
}
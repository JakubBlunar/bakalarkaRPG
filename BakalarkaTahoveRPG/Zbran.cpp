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





void Zbran::pouzi(Hrac* hrac) {
	std::map<int, Predmet*>* oblecene = hrac->Getstatistika()->Getoblecene();
	Pouzitelny* docasny1;
	Pouzitelny* docasny2;

	if (!Pouzitelny::Isobleceny()) {
		int typ = Gettyp();

		if (typ == 1) {
			
			if (oblecene->count(1)) {

				if (oblecene->count(2)) {
					docasny1 =(Pouzitelny*)oblecene->at(1);
					oblecene->erase(1);
					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
					
					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);
					Pouzitelny::Setobleceny(true);
					
				}
				else {// na slote 2 nie je žiadna zbran
					docasny1 = (Pouzitelny*)oblecene->at(1);
					if (docasny1->Gettyp() != 2) {//nie je obojrucna
						Pouzitelny::Setobleceny(true);
						oblecene->insert(std::pair<int, Predmet*>(2, this));
						hrac->Getinventar()->zmazPredmet(this);
					}
					else { // ak je obojruèna tak može drža len tu
						oblecene->erase(1);
						docasny1->Setobleceny(false);
						hrac->Getinventar()->pridajPredmet(docasny1);

						Pouzitelny::Setobleceny(true);
						oblecene->insert(std::pair<int, Predmet*>(2, this));
						hrac->Getinventar()->zmazPredmet(this);
					}
				}


			}
			else {
				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(1, this));
				hrac->Getinventar()->zmazPredmet(this);
			}

		}
		else if (typ == 2) { // je to obojruèna
			if (oblecene->count(1)) {
				if (oblecene->count(2)) {

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
				else {
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
				if (oblecene->count(2)) {
					docasny1 = (Pouzitelny*)oblecene->at(2);
					oblecene->erase(2);
					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);

					Pouzitelny::Setobleceny(true);
					oblecene->insert(std::pair<int, Predmet*>(1, this));
					hrac->Getinventar()->zmazPredmet(this);
				}
				else {
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
		}
	
				
	}
	else {

	}
}
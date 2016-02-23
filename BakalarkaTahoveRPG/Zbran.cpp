#include "Zbran.h"

#include "Hrac.h"
#include "Statistika.h"
#include "Inventar.h"

Zbran::Zbran(std::string meno, int typ, std::string paObrazok, int cena, int paUroven, int paMinPoskodenie, int paMaxPoskodnie,int rychlostUtoku) :Pouzitelny(meno, typ, paObrazok, cena, paUroven) {
	minPoskodenie = paMinPoskodenie;
	maxPoskodenie = paMaxPoskodnie;
	this->rychlostUtoku = rychlostUtoku;
}



Zbran::~Zbran() {
	Pouzitelny::~Pouzitelny();
}


int Zbran::Getminposkodenie() {
	return minPoskodenie;
}
int Zbran::Getmaxposkodenie() {
	return maxPoskodenie;
}


/*
	hnusné riešenie a nepaèi sa mi :D
*/

void Zbran::pouzi(Hrac* hrac) {

	if (hrac->Getstatistika()->dajUroven() < this->Geturoven()) return;

	std::map<int, Predmet*>* oblecene = hrac->Getstatistika()->Getoblecene();
	Pouzitelny* docasny1;
	Pouzitelny* docasny2;

	int typ = Gettyp();

	if (!Pouzitelny::Isobleceny()) {
		
		int moznost = 0;;
		if (oblecene->count(9)) {
			moznost +=1;
		}

		if (oblecene->count(10)) {
			moznost += 2;
		}

		if (moznost == 0) {
			if (typ == 9) {
				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);
			}
			else if (typ == 10) {
				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);
			}
			else {
				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(10, this));
				hrac->Getinventar()->zmazPredmet(this);
			}
		}

		if (moznost == 1) { // daèo je na prvom slote

			if(typ == 9){
				docasny1 = (Pouzitelny*)oblecene->at(9);
				if (docasny1->Gettyp() == 10) {
					oblecene->erase(9);
					oblecene->insert(std::pair<int, Predmet*>(9, this));
					hrac->Getinventar()->zmazPredmet(this);

					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);
					Pouzitelny::Setobleceny(true);
				}
				else {
					Pouzitelny::Setobleceny(true);
					oblecene->insert(std::pair<int, Predmet*>(10, this));
					hrac->Getinventar()->zmazPredmet(this);
				}
			}
			else if (typ == 10) {
				docasny1 = (Pouzitelny*)oblecene->at(9);
				oblecene->erase(9);
				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);

				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);
				Pouzitelny::Setobleceny(true);
			}
			else {
				docasny1 = (Pouzitelny*)oblecene->at(9);
				if (docasny1->Gettyp() == 10) {
					oblecene->erase(9);
					oblecene->insert(std::pair<int, Predmet*>(10, this));
					hrac->Getinventar()->zmazPredmet(this);

					docasny1->Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(docasny1);
					Pouzitelny::Setobleceny(true);

				}
				else {
					Pouzitelny::Setobleceny(true);
					oblecene->insert(std::pair<int, Predmet*>(10, this));
					hrac->Getinventar()->zmazPredmet(this);
				}
			}	
		}


		if (moznost == 2) { // daèo je na druhom slote

			if (typ == 9) {
				Pouzitelny::Setobleceny(true);
				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);
			}
			else if (typ == 10) {
				docasny1 = (Pouzitelny*)oblecene->at(10);
				oblecene->erase(10);
				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);

				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);
				Pouzitelny::Setobleceny(true);
			}
			else {

				docasny1 = (Pouzitelny*)oblecene->at(10);
				oblecene->erase(10);
				oblecene->insert(std::pair<int, Predmet*>(10, this));
				hrac->Getinventar()->zmazPredmet(this);

				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);
				Pouzitelny::Setobleceny(true);
			}
		}


		if (moznost == 3) { // daèo je na prvom a druhom slote 

			if (typ == 9) {
				docasny1 = (Pouzitelny*)oblecene->at(9);
				oblecene->erase(9);
				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);

				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);
				Pouzitelny::Setobleceny(true);
			}
			else if (typ == 10) {
				
				docasny1 = (Pouzitelny*)oblecene->at(9);
				docasny2 = (Pouzitelny*)oblecene->at(10);

				oblecene->erase(9);
				oblecene->erase(10);

				oblecene->insert(std::pair<int, Predmet*>(9, this));
				hrac->Getinventar()->zmazPredmet(this);

				docasny2->Setobleceny(false);
				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);
				hrac->Getinventar()->pridajPredmet(docasny2);

				Pouzitelny::Setobleceny(true);
			}
			else {

				docasny1 = (Pouzitelny*)oblecene->at(10);
				oblecene->erase(10);
				oblecene->insert(std::pair<int, Predmet*>(10, this));
				hrac->Getinventar()->zmazPredmet(this);

				docasny1->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny1);
				Pouzitelny::Setobleceny(true);
			}
		}

		
				
	}
	else { // predmet je oblecenı tak sa vyzlecie
		for (int i = 9; i <= 10; i++) {
			if (oblecene->count(i)) {
				if (oblecene->at(i) == this) {
					Pouzitelny::Setobleceny(false);
					hrac->Getinventar()->pridajPredmet(this);
					oblecene->erase(i);

				}
			}
		}

	}

	hrac->Getstatistika()->prepocitajPoskodenia();
}

int Zbran::GetrychlostUtoku() {
	return rychlostUtoku;
}
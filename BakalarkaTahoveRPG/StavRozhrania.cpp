#include "StavRozhrania.h"


StavRozhrania::StavRozhrania(Stav* pociatocnyStav) {
	pridajStav(pociatocnyStav);
	aktualnyStav = pociatocnyStav;
	nasledujuci = nullptr;

}

StavRozhrania::~StavRozhrania() {
	
	for (std::map<std::string, Stav*>::iterator it = stavy.begin(); it != stavy.end(); ++it)
	{
		delete(it->second);
	}
	stavy.clear();

}


void StavRozhrania::zmenMapu() {

}

void StavRozhrania::update(double cas) {
	if (nasledujuci != nullptr && !aktualnyStav->GetzobrazujePopup()) {
		zmenStav(nasledujuci->Getnazov());
	}
	else {
		aktualnyStav->update(cas);
	}
}

void StavRozhrania::render() {
	aktualnyStav->render();
}


void StavRozhrania::pridajStav(Stav* stav) {
	stavy.insert(std::pair<std::string, Stav*>(stav->Getnazov(), stav));
}


Stav* StavRozhrania::GetaktualnyStav() {
	return aktualnyStav;
}


void StavRozhrania::zmenStav(std::string stav) {
	if (aktualnyStav->GetzobrazujePopup()) {
		nasledujuci = stavy.at(stav);
	}
	else {
		aktualnyStav->onExit();
		aktualnyStav = stavy.at(stav);
		aktualnyStav->onEnter();
		nasledujuci = nullptr;
	}
}


Stav* StavRozhrania::dajStav(std::string stav) {

	if (stav == "") {
		return aktualnyStav;
	}

	if (stavy.find(stav) == stavy.end()) {
		return nullptr;
	}
	else {
		return stavy.at(stav);
	}
}
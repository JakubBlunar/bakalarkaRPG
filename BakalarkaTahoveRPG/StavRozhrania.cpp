#include "StavRozhrania.h"


StavRozhrania::StavRozhrania(Stav* pociatocnyStav) {
	pridajStav(pociatocnyStav);
	aktualnyStav = pociatocnyStav;

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
	aktualnyStav->update(cas);
}

void StavRozhrania::render(sf::RenderWindow* okno) {
	aktualnyStav->render(okno);
}


void StavRozhrania::pridajStav(Stav* stav) {
	stavy.insert(std::pair<std::string, Stav*>(stav->Getnazov(), stav));
	std::cout << "Stav " << stav->Getnazov() << "bol pridany" << std::endl;
}


Stav* StavRozhrania::GetaktualnyStav() {
	return aktualnyStav;
}


void StavRozhrania::zmenStav(std::string stav) {
	aktualnyStav->onExit();
	aktualnyStav = stavy.at(stav);
	aktualnyStav->onEnter();
}


Stav* StavRozhrania::dajStav(std::string stav) {
	return stavy.at(stav) == nullptr ? nullptr : stavy.at(stav);
}
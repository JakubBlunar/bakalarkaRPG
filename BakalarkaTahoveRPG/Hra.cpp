#include "Hra.h"
#include "Loader.h"

#include "StavRozhrania.h"
#include "StavVolbaZamerania.h"
#include "StavHlavneMenu.h"
#include "StavHranieHry.h"
#include "StavPauza.h"
#include "StavInfoHraca.h"
#include "StavInventar.h"
#include "StavDialog.h"
#include "StavBoj.h"
#include "StavObchod.h"
#include "StavPrehladQuestov.h"

#define NAZOV "Moje Rpg"


Hra::Hra() {
	hrac = nullptr;
	init();
	loader->setHra(this);

	std::string nazov = "hlavneMenu";
	Stav* stav1 = new StavHlavneMenu(nazov, okno, this);

	stavRozhraniaHry = new StavRozhrania(stav1);

	std::string nazov2 = "volbaZamerania";
	Stav* stav2 = new StavVolbaZamerania(nazov2, okno, this);
	stavRozhraniaHry->pridajStav(stav2);

	std::string nazov3 = "hranieHry";
	Stav* stav3 = new StavHranieHry(nazov3, okno, this,nullptr);
	stavRozhraniaHry->pridajStav(stav3);

	std::string nazov4 = "stavPauza";
	Stav* stav4 = new StavPauza(nazov4, okno, this);
	stavRozhraniaHry->pridajStav(stav4);

	std::string nazov6 = "stavInfoHraca";
	Stav* stav6 = new StavInfoHraca(nazov6, okno, this);
	stavRozhraniaHry->pridajStav(stav6);

	std::string nazov7 = "stavInventar";
	Stav* stav7 = new StavInventar(nazov7, okno, this);
	stavRozhraniaHry->pridajStav(stav7);

	std::string nazov8 = "stavDialog";
	Stav* stav8 = new StavDialog(nazov8, okno, this);
	stavRozhraniaHry->pridajStav(stav8);

	std::string nazov9 = "stavBoj";
	Stav* stav9 = new StavBoj(nazov9, okno, this);
	stavRozhraniaHry->pridajStav(stav9);

	std::string nazov10 = "stavObchod";
	Stav* stav10 = new StavObchod(nazov10, okno, this);
	stavRozhraniaHry->pridajStav(stav10);

	std::string nazov11 = "stavPrehladQuestov";
	Stav* stav11 = new StavPrehladQuestov(nazov11, okno, this);
	stavRozhraniaHry->pridajStav(stav11);

}

Hra::~Hra() {
	delete(stavRozhraniaHry);
	delete(okno);
}


void Hra::start() {
	hlavnaSlucka();

}


void Hra::hlavnaSlucka() {
	const sf::Time ObnovovaciCas = sf::seconds(1.f / 120.f);
	sf::Clock clock;
	sf::Time casOdPoslednehoUpdate = sf::Time::Zero;

	while (okno->isOpen())
	{
		sf::Event event;
		while (okno->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno->close();
			if (event.type == sf::Event::GainedFocus) 
				focus = true;
			if (event.type == sf::Event::LostFocus) 
				focus = false;

		}

		sf::Time uplynulyCas = clock.restart();
		casOdPoslednehoUpdate += uplynulyCas;
		while (casOdPoslednehoUpdate > ObnovovaciCas){
			casOdPoslednehoUpdate -= ObnovovaciCas;
			stavRozhraniaHry->update(20);
		}
			
		if (focus) {
			okno->clear();
			stavRozhraniaHry->render();
		}


		okno->display();
	}

}

void Hra::zmenStavRozhrania(std::string paStav) {
	stavRozhraniaHry->zmenStav(paStav);
}

void Hra::SetHrac(Hrac* paHrac) {
	hrac = paHrac;
}

bool Hra::maFocus() {
	return focus;
}

Hrac* Hra::GetHrac() {
	return hrac;
}

Stav* Hra::dajStav(std::string stav) {
	return stavRozhraniaHry->dajStav(stav);
}

void Hra::init() {
	loader = Loader::Instance();
	focus = true;

	okno = new sf::RenderWindow(sf::VideoMode(1024, 700), NAZOV,sf::Style::Titlebar|sf::Style::Close);
	okno->setFramerateLimit(60);
	okno->setVerticalSyncEnabled(true);
	if (sf::VideoMode::getDesktopMode().height < 769) {
		okno->setPosition(sf::Vector2i(okno->getPosition().x, 0));
	}
}
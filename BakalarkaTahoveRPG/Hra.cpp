#include "Hra.h"
#include "Loader.h"

#include "StavRozhrania.h"
#include "StavVolbaZamerania.h"
#include "StavHlavneMenu.h"
#include "StavHranieHry.h"
#include "StavPauza.h"

#define NAZOV "SUPERRPG"


Hra::Hra() {

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
	
}

Hra::~Hra() {
	delete(stavRozhraniaHry);
	delete(okno);
}


void Hra::start() {
	hlavnaSlucka();
}


void Hra::hlavnaSlucka() {
	const sf::Time ObnovovaciCas = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time casOdPoslednehoUpdate = sf::Time::Zero;

	while (okno->isOpen())
	{
		sf::Event event;
		while (okno->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno->close();

		}

		if (!loader->Getnacitava()) {	
			sf::Time uplynulyCas = clock.restart();
			casOdPoslednehoUpdate += uplynulyCas;
			while (casOdPoslednehoUpdate > ObnovovaciCas)
			{
				casOdPoslednehoUpdate -= ObnovovaciCas;
				stavRozhraniaHry->update(20);
			}
			
			okno->clear();
			stavRozhraniaHry->render();
			okno->display();
		}
		else {
			okno->clear();
			okno->draw(textNacitanie);
			okno->display();
		}
	}

}

void Hra::zmenStavRozhrania(std::string paStav) {
	stavRozhraniaHry->zmenStav(paStav);
}

void Hra::SetHrac(Hrac* paHrac) {
	hrac = paHrac;
}


Hrac* Hra::GetHrac() {
	return hrac;
}

Stav* Hra::dajStav(std::string stav) {
	return stavRozhraniaHry->dajStav(stav);
}

void Hra::init() {

	font = new sf::Font();
	if (!font->loadFromFile("Data/Grafika/font.ttf")) {
		exit(1);
	};

	textNacitanie.setFont(*font);
	textNacitanie.setString("Nacitavam");
	textNacitanie.setCharacterSize(128);
	textNacitanie.setPosition(sf::Vector2f(100, 100));


	okno = new sf::RenderWindow(sf::VideoMode(1024, 768), NAZOV);
	okno->setFramerateLimit(60);
	okno->setVerticalSyncEnabled(true);

	loader = Loader::Instance();
}
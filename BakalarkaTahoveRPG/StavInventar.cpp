#include "StavInventar.h"
#include "Hra.h"
#include "Hrac.h"
#include "Statistika.h"
#include "Zameranie.h"
#include "Inventar.h"



StavInventar::StavInventar(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font2.otf");
	
	
	sf::Texture texture;
	texture.create(200, 200);
	
	ukazovatel = new sf::Sprite();
	ukazovatel->setTexture(texture);
	ukazovatel->setTextureRect(sf::IntRect(0, 0, 48, 48));
	ukazovatel->setColor(sf::Color(0, 0, 255, 128));
	oznacene = 1;
}


StavInventar::~StavInventar() {
	delete(font);
	delete(ukazovatel);
}



void StavInventar::onEnter() {
	Stav::onEnter();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		stlacenaKlavesa = true;
	}

	hrac = hra->GetHrac();
	inventar = hrac->Getinventar();
}


void StavInventar::onExit() {
	Stav::onExit();
}


void StavInventar::render() {

	int startX = 20;
	int startY = 70;
	int nasirku = 18;

	sf::Text text("Inventar", *font, 45U);
	text.setPosition(sf::Vector2f(10.f, 10.f));
	okno->draw(text);

	//text.setCharacterSize(35U);
	//text.setString(hrac->GetZameranie()->Getnazov());
	//text.setPosition(sf::Vector2f(32.f, 56.f));
	//okno->draw(text);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(48, 48));


	sf::Sprite* predmetObrazok;
	for (int i = 0; i < inventar->Getkapacita(); i++) {
		
		rectangle.setPosition(startX + (i%nasirku)*55 , startY + (i/nasirku)*55);
		okno->draw(rectangle);

		if (i < inventar->pocetPredmetov()) {
			
			predmetObrazok = inventar->dajPredmetNaIndexe(i)->Getobrazok();
			predmetObrazok->setScale(sf::Vector2f(1.5f, 1.5f));
			predmetObrazok->setPosition(sf::Vector2f(startX + (i%nasirku) * 55, startY + (i / nasirku) * 55));

			okno->draw(*predmetObrazok);
		}


		if (i == oznacene) {
			ukazovatel->setPosition(sf::Vector2f(startX + (i%nasirku) * 55, startY + (i / nasirku) * 55));
			okno->draw(*ukazovatel);
		}
	}

	//std::cout << oznacene << std::endl;
}


void StavInventar::update(double delta) {

	if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::I))) {
		hra->zmenStavRozhrania("hranieHry");
	}

	if (stlacenaKlavesa && !sf::Keyboard::isKeyPressed(sf::Keyboard::I) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		stlacenaKlavesa = false;
	}
}
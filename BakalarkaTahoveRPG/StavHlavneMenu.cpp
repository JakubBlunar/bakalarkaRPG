
#include "StavHlavneMenu.h"
#include "Hra.h"

StavHlavneMenu::StavHlavneMenu(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra): Stav(paNazov,paOkno,paHra){
	moznosti.push_back("Nová hra");
	moznosti.push_back("Nacitaj");
	moznosti.push_back("Koniec");
	oznacene = 0;
	
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font2.otf");

}


StavHlavneMenu::~StavHlavneMenu() {
	moznosti.clear();
	delete(font);
}



void StavHlavneMenu::onEnter() {
	Stav::onEnter();
}


void StavHlavneMenu::onExit() {
	Stav::onExit();
}


void StavHlavneMenu::render() {

	for (unsigned int i = 0; i < moznosti.size(); i++)
	{
		sf::Text text(moznosti.at(i), *font, 75U);

		if(oznacene == i){
			text.setColor(sf::Color::Blue);
		}
		else {
			text.setColor(sf::Color::White);
		}
		text.setPosition(sf::Vector2f(sf::Vector2f(100.f, 100+75.f*i)));

		okno->draw(text);
	}
	

	//std::cout << oznacene << std::endl;
}


void StavHlavneMenu::update(double delta) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !stlacenaKlavesa) {
		stlacenaKlavesa = true;
		if (oznacene > 0) {
			oznacene--;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !stlacenaKlavesa) {
		stlacenaKlavesa = true;
		if (oznacene < (signed int)moznosti.size()-1) {
			oznacene++;
		}
	}
	
	if (oznacene == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
		stlacenaKlavesa = true;
		hra->zmenStavRozhrania("volbaZamerania");
	}

	if (oznacene == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
		stlacenaKlavesa = true;
		okno->close();
	}


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		stlacenaKlavesa = false;
	}

}
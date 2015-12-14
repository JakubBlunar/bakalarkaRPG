
#include "StavLoading.h"
#include "Hra.h"

StavLoading::StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = new sf::Font();
	font->loadFromFile("Data/Grafika/font.ttf");
	

}


StavLoading::~StavLoading() {
	delete(font);
}



void StavLoading::onEnter() {
	Stav::onEnter();
}


void StavLoading::onExit() {
	Stav::onExit();
}


void StavLoading::render() {

		//okno->draw(text);


	//std::cout << oznacene << std::endl;
}


void StavLoading::update(double delta) {

}
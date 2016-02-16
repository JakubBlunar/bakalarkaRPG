
#include "StavLoading.h"
#include "Loader.h"
#include "Hra.h"


StavLoading::StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	font = Loader::Instance()->nacitajFont("font2.otf");
}


StavLoading::~StavLoading() {
}



void StavLoading::onEnter() {
	Stav::onEnter();
}


void StavLoading::onExit() {
	Stav::onExit();
}


void StavLoading::render() {
	Stav::render();
		//okno->draw(text);


	//std::cout << oznacene << std::endl;
}


void StavLoading::update(double delta) {

}
#include "StavLoading.h"
#include "Hra.h"

StavLoading::StavLoading(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) :Stav(paNazov, paOkno, paHra)
{
	

}


StavLoading::~StavLoading()
{
	

}



void StavLoading::onEnter() {

	Stav::onEnter();
}





void StavLoading::onExit() {
	Stav::onExit();
}


void StavLoading::render() {
	sf::Text t("Loading ...", *font, 50U);
	okno->draw(t);

	Stav::render();
}


void StavLoading::update(double delta) {

	if (hra->maFocus()) {
		Stav::update(delta);
		if (stav == StavAkcia::NORMAL) {
			

		}
	}
}

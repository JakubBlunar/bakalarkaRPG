#include "Tlacidlo.h"
#include <iostream>

Tlacidlo::Tlacidlo(sf::Sprite* normalne, sf::Sprite* kliknute, std::string paText, sf::Vector2f pozicia,sf::Vector2f velkost,sf::Font *font, unsigned int velkostPisma) {
	this->normalne = normalne;
	this->kliknute = kliknute;
	this->aktualne = normalne;
	this->pozicia = pozicia;
	this->velkost = velkost;

	this->zakliknute = false;
	text.setFont(*font);
	text.setString(paText);
	text.setCharacterSize(velkostPisma);
	text.setPosition(pozicia.x + 3, pozicia.y + 3);
}
void Tlacidlo::skontrolujKlik(sf::Vector2i mousePos) {
	if (mousePos.x>pozicia.x && mousePos.x<(pozicia.x + velkost.x)) {
		if (mousePos.y>pozicia.y && mousePos.y<(pozicia.y + velkost.y)) {
			//std::cout << "Stlacene Tlacidlo" << text.getString().toAnsiString() << std::endl;
			Setzakliknute(!zakliknute);
		}
	}
}
void Tlacidlo::Setzakliknute(bool ake) {
	zakliknute = ake;
	if (zakliknute) {
		aktualne = kliknute;
		return;
	}
	aktualne = normalne;
}
void Tlacidlo::Settext(std::string words) {
	text.setString(words);
}
bool Tlacidlo::Getzakliknute() {
	return zakliknute;
}
sf::Sprite* Tlacidlo::Getsprite() {
	aktualne->setPosition(pozicia);
	aktualne->setTextureRect(sf::IntRect(0, 0,(int) velkost.x,(int) velkost.y));
	return aktualne;
}

sf::Text Tlacidlo::Gettext() {
	return text;
}
#include "Tlacidlo.h"

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

Tlacidlo::~Tlacidlo() {
	delete normalne;
	if (kliknute != nullptr) {
		delete kliknute;
	}
}

void Tlacidlo::skontrolujKlik(sf::Vector2i mousePos) {
	if (mousePos.x>pozicia.x && mousePos.x<(pozicia.x + velkost.x)) {
		if (mousePos.y>pozicia.y && mousePos.y<(pozicia.y + velkost.y)) {
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
bool Tlacidlo::Getzakliknute() const
{
	return zakliknute;
}
sf::Sprite* Tlacidlo::Getsprite() const
{
	aktualne->setPosition(pozicia);
	aktualne->setTextureRect(sf::IntRect(0, 0,static_cast<int>(velkost.x),static_cast<int>(velkost.y)));
	return aktualne;
}

sf::Text Tlacidlo::Gettext() {
	text.setPosition(pozicia);
	return text;
}

bool Tlacidlo::hover(sf::Vector2i mousePos) const
{
	if (mousePos.x>pozicia.x && mousePos.x<(pozicia.x + velkost.x)) {
		if (mousePos.y>pozicia.y && mousePos.y<(pozicia.y + velkost.y)) {
			return true;
		}
	}

	return false;
}

sf::Vector2f Tlacidlo::getPosition() const
{
	return pozicia;
}

sf::FloatRect Tlacidlo::getGlobalBounds() const
{
	return sf::FloatRect(pozicia.x, pozicia.y, velkost.x, velkost.y);
}

sf::RectangleShape Tlacidlo::Getramcek() const
{
	sf::RectangleShape ramcek(velkost);
	ramcek.setPosition(pozicia);
	ramcek.setOutlineThickness(1);
	return ramcek;
}

void Tlacidlo::setSize(sf::Vector2f paVelkost) {
	velkost = paVelkost;
}

void Tlacidlo::Setpozicia(sf::Vector2f paPozicia) {
	pozicia = paPozicia;
}

sf::Vector2f Tlacidlo::getSize() const
{
	return velkost;
}

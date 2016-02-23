#include "StavBoj.h"
#include "Hra.h"
#include "Boj.h"
#include "Loader.h"
#include "Tlacidlo.h"

#include "Statistika.h"
#include "Akcia.h"
#include "AkciaDmg.h"
#include "AkciaPoskodenieZbranou.h"
#include "AkciaLiecenie.h"
#include "PopupOkno.h"

#include <math.h>

StavBoj::StavBoj(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra):Stav(paNazov,paOkno,paHra)
{
	font = Loader::Instance()->nacitajFont("font2.otf");
	boj = nullptr;

	

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			sf::Texture textura;
			bool uspech = false;
			while (!uspech) {
				uspech = textura.create(50, 50);
			}
			sf::Sprite* normalne = new sf::Sprite();
			sf::Sprite* zakliknute = new sf::Sprite(textura);
			zakliknute->setTextureRect(sf::IntRect(0, 0, 48, 48));
			while (zakliknute->getColor() != sf::Color(255, 0, 0, 128)) {
				zakliknute->setColor(sf::Color(255, 0, 0, 128));
			}
			tlacidla[i][j] = new Tlacidlo(zakliknute,normalne, "", sf::Vector2f(280.f+ j*50, okno->getSize().y - 200.f + 20.f + i*50), sf::Vector2f(48,48), font, 35U);
		}
	}


}


StavBoj::~StavBoj()
{
}



void StavBoj::onEnter() {
	
	Stav::onEnter();
	if (boj == nullptr) {
		hra->zmenStavRozhrania("hranieHry");
	}
	else {
		boj->bojStart();
	}
	

}





void StavBoj::onExit() {
	Stav::onExit();
}


void StavBoj::render() {

	int startX = 20;
	int startY = 70;

	sf::RectangleShape pozadieAkcie;
	pozadieAkcie.setFillColor(sf::Color(211, 211, 211));
	pozadieAkcie.setSize(sf::Vector2f(okno->getSize().x + 0.f, 200.f));
	pozadieAkcie.setPosition(sf::Vector2f(0, okno->getSize().y - pozadieAkcie.getSize().y));
	okno->draw(pozadieAkcie);

	int hracHp = boj->Gethracovastatistika()->Gethp();
	int hracMaxHp = boj->Gethracovastatistika()->GethpMax();
	int hracMp = boj->Gethracovastatistika()->Getmp();
	int hracMaxMp = boj->Gethracovastatistika()->GetmpMax();

	sf::RectangleShape hpBarZadny;
	hpBarZadny.setFillColor(sf::Color::Black);
	hpBarZadny.setSize(sf::Vector2f(50.f, 150.f));
	hpBarZadny.setPosition(sf::Vector2f(20.f, okno->getSize().y - pozadieAkcie.getSize().y + 20.f));


	sf::RectangleShape hpBarPredny;
	hpBarPredny.setFillColor(sf::Color::Red);
	hpBarPredny.setSize(sf::Vector2f(50.f, ((float)hracHp / hracMaxHp)*hpBarZadny.getSize().y));
	hpBarPredny.setPosition(sf::Vector2f(20.f, okno->getSize().y - pozadieAkcie.getSize().y + 20.f + (1 - ((float)hracHp / hracMaxHp))*hpBarZadny.getSize().y));

	okno->draw(hpBarZadny);
	okno->draw(hpBarPredny);

	sf::RectangleShape mpBarZadny;
	mpBarZadny.setFillColor(sf::Color::Black);
	mpBarZadny.setSize(sf::Vector2f(50.f, 150.f));
	mpBarZadny.setPosition(sf::Vector2f(okno->getSize().x - 70.f, okno->getSize().y - pozadieAkcie.getSize().y + 20.f));

	sf::RectangleShape mpBarPredny;
	mpBarPredny.setFillColor(sf::Color::Blue);
	mpBarPredny.setSize(sf::Vector2f(50.f, ((float)hracMp / hracMaxMp)*mpBarZadny.getSize().y));
	mpBarPredny.setPosition(sf::Vector2f(okno->getSize().x - 70.f, okno->getSize().y - pozadieAkcie.getSize().y + 20.f + +(1 - ((float)hracMp / hracMaxMp))*mpBarZadny.getSize().y));

	okno->draw(mpBarZadny);
	okno->draw(mpBarPredny);

	sf::Text text("", *font, 18U);
	text.setColor(sf::Color::Black);

	text.setString(std::to_string(hracHp) + "/" + std::to_string(hracMaxHp));
	text.setPosition(sf::Vector2f(10, hpBarZadny.getGlobalBounds().top + hpBarZadny.getSize().y));
	okno->draw(text);

	text.setString(std::to_string(hracMp) + "/" + std::to_string(hracMaxMp));
	text.setPosition(sf::Vector2f(okno->getSize().x - 10 - text.getLocalBounds().width, mpBarZadny.getGlobalBounds().top + mpBarZadny.getSize().y));
	okno->draw(text);

	std::vector<Akcia*>* hracoveAkcie = boj->Gethracovastatistika()->Getakcie();
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			unsigned int index = i * 3 + j;
			if (index < hracoveAkcie->size()) {
				sf::Sprite* obrazok = hracoveAkcie->at(index)->Getobrazok();
				obrazok->setScale(1.5, 1.5);
				obrazok->setPosition(tlacidla[i][j]->getPosition().x, tlacidla[i][j]->getPosition().y);
				okno->draw(*obrazok);
			}
		}
	}

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(48, 48));
	rect.setFillColor(sf::Color(255, 0, 0, 128));

	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			unsigned int index = i * 3 + j;
			if (index < hracoveAkcie->size()) {
				if (boj->maAkciaCooldown(hracoveAkcie->at(index))) {
					rect.setPosition(tlacidla[i][j]->getPosition().x, tlacidla[i][j]->getPosition().y);
					okno->draw(rect);
				}
			}
		}
	}

	sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			unsigned int index = i * 3 + j;
			if (tlacidla[i][j]->hover(pozicia) && index < hracoveAkcie->size()) {




				sf::RectangleShape akciaInfo;
				akciaInfo.setFillColor(sf::Color::White);
				akciaInfo.setOutlineThickness(2);
				akciaInfo.setOutlineColor(sf::Color::Red);
				akciaInfo.setSize(sf::Vector2f(250, 150));
				akciaInfo.setPosition(tlacidla[0][0]->Getsprite()->getPosition().x + 50 * (j + 1) - 10, tlacidla[0][0]->Getsprite()->getPosition().y + 50 * i - akciaInfo.getSize().y + 10);
				okno->draw(akciaInfo);

				Akcia* akcia = hracoveAkcie->at(index);
				sf::Text popisAkcie(akcia->Getmeno(), *font, 18U);
				popisAkcie.setColor(sf::Color::Black);
				popisAkcie.setPosition(akciaInfo.getGlobalBounds().left + 3, akciaInfo.getGlobalBounds().top + 3);
				okno->draw(popisAkcie);

				std::string popis = "";
				if (akcia->Getcenamany() != 0) {
					popis += "Mana: " + std::to_string(akcia->Getcenamany()) + "\n";
				}

				if (dynamic_cast<AkciaDmg*>(akcia) != NULL) {
					AkciaDmg* dmgakcia = (AkciaDmg*)akcia;
					popis += "Poskodenie:" + std::to_string(dmgakcia->minPoskodenie(boj->Gethracovastatistika())) + " - " + std::to_string(dmgakcia->maxPoskodenie(boj->Gethracovastatistika())) + "\n";
				}

				if (dynamic_cast<AkciaPoskodenieZbranou*>(akcia) != NULL) {
					AkciaPoskodenieZbranou* dmgakcia = (AkciaPoskodenieZbranou*)akcia;
					popis += "Poskodenie:" + std::to_string(dmgakcia->minPoskodenie()) + " - " + std::to_string(dmgakcia->maxPoskodenie()) + "\n";
				}

				if (dynamic_cast<AkciaLiecenie*>(akcia) != NULL) {
					AkciaLiecenie* liecenieAkcia = (AkciaLiecenie*)akcia;
					popis += "Liecenie:" + std::to_string(liecenieAkcia->minLiecenie(boj->Gethracovastatistika())) + " - " + std::to_string(liecenieAkcia->maxLiecenie(boj->Gethracovastatistika())) + "\n";
				}

				if (akcia->GetcasCastenia() != 0) {
					popis += "Cas castenia:" + std::to_string(akcia->GetcasCastenia()) + "ms\n";
				}
				if (akcia->Getcooldown() != 0) {
					popis += "Cooldown:" + std::to_string(akcia->Getcooldown()) + "ms\n";
				}
				popisAkcie.setString(popis);
				popisAkcie.setCharacterSize(14);
				popisAkcie.setPosition(akciaInfo.getGlobalBounds().left + 3, akciaInfo.getGlobalBounds().top + 25);
				okno->draw(popisAkcie);

			}
		}
	}

	text.setColor(sf::Color::White);
	text.setString("cas" + std::to_string(boj->Getcasvboji().asMilliseconds()) + " ms");
	text.setPosition(sf::Vector2f(10, 10));
	okno->draw(text);

	//npc

	int npcHp = boj->Getnpcstatistika()->Gethp();
	int npcMaxHp = boj->Getnpcstatistika()->GethpMax();
	int npcMp = boj->Getnpcstatistika()->Getmp();
	int npcMaxMp = boj->Getnpcstatistika()->GetmpMax();

	sf::RectangleShape npcHpBarZadny;
	npcHpBarZadny.setFillColor(sf::Color::White);
	npcHpBarZadny.setSize(sf::Vector2f(150.f, 50.f));
	npcHpBarZadny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 20.f));


	sf::RectangleShape npcHpBarPredny;
	npcHpBarPredny.setFillColor(sf::Color::Red);
	npcHpBarPredny.setSize(sf::Vector2f(((float)npcHp / npcMaxHp)*150.f, 50.f));
	npcHpBarPredny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 20.f));

	okno->draw(npcHpBarZadny);
	okno->draw(npcHpBarPredny);

	sf::RectangleShape npcMpBarZadny;
	npcMpBarZadny.setFillColor(sf::Color::White);
	npcMpBarZadny.setSize(sf::Vector2f(150.f, 50.f));
	npcMpBarZadny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 80.f));

	sf::RectangleShape npcMpBarPredny;
	npcMpBarPredny.setFillColor(sf::Color::Blue);
	npcMpBarPredny.setSize(sf::Vector2f(((float)npcMp / npcMaxMp)*150.f, 50.f));
	npcMpBarPredny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 80.f));

	okno->draw(npcMpBarZadny);
	okno->draw(npcMpBarPredny);

	text.setString(std::to_string(npcHp) + "/" + std::to_string(npcMaxHp));
	text.setPosition(sf::Vector2f(npcHpBarZadny.getGlobalBounds().left - text.getGlobalBounds().width - 10, 25.f));
	okno->draw(text);

	text.setString(std::to_string(npcMp) + "/" + std::to_string(npcMaxMp));
	text.setPosition(sf::Vector2f(npcHpBarZadny.getGlobalBounds().left - text.getGlobalBounds().width - 10, 85.f));
	okno->draw(text);
	
	//cast bar
	if (boj->castBarProgres() != -1) {

		sf::RectangleShape castZadny;
		castZadny.setFillColor(sf::Color::White);
		castZadny.setSize(sf::Vector2f(250, 35.f));
		castZadny.setPosition(sf::Vector2f(50, okno->getSize().y - pozadieAkcie.getSize().y - 50));


		sf::RectangleShape castPredny;
		castPredny.setFillColor(sf::Color::Green);
		castPredny.setSize(sf::Vector2f(boj->castBarProgres()*castZadny.getSize().x, castZadny.getSize().y));
		castPredny.setPosition(sf::Vector2f(castZadny.getGlobalBounds().left, castZadny.getGlobalBounds().top));

		okno->draw(castZadny);
		okno->draw(castPredny);
	}

	Stav::render();
}


void StavBoj::update(double delta) {

	if (hra->maFocus()) {
		Stav::update(delta);
		if (stav == StavAkcia::NORMAL) {
			boj->update();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
			{
				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
				if (boj->cakaNaVybratieAkcie() && !boj->koniecBoja()) {
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 9; j++) {
							unsigned int index = i * 3 + j;
							tlacidla[i][j]->skontrolujKlik(pozicia);
							if (tlacidla[i][j]->Getzakliknute() && index < boj->Gethracovastatistika()->Getakcie()->size()) {
								if (!boj->maAkciaCooldown(boj->Gethracovastatistika()->Getakcie()->at(index))) {
									boj->hracVybralAkciu(boj->Gethracovastatistika()->Getakcie()->at(index));
								}
							}
							tlacidla[i][j]->Setzakliknute(false);
						}

					}
				}
				stlacenaMys = true;
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == true) {
				stlacenaMys = false;
			}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					stlacenaKlavesa = true;
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					stlacenaKlavesa = true;
				}

				if (!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					stlacenaKlavesa = true;
	
				}
			
	
			if (stlacenaKlavesa
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
				) {
				stlacenaKlavesa = false;
			}
		}
	}
}

void StavBoj::setBoj(Boj* paBoj) {
	if (boj != nullptr) {
		delete boj;
	}
	boj = paBoj;
}



#include "StavBoj.h"
#include "Hra.h"
#include "Boj.h"
#include "Loader.h"
#include "Tlacidlo.h"
#include "Hrac.h"

#include "Statistika.h"
#include "Akcia.h"
#include "AkciaDmg.h"
#include "AkciaPoskodenieZbranou.h"
#include "AkciaLiecenie.h"
#include "PopupOkno.h"
#include "AkciaPridanieEfektu.h"
#include "Efekt.h"
#include "Nepriatel.h"
#include <math.h>

StavBoj::StavBoj(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra):Stav(paNazov,paOkno,paHra)
{
	boj = nullptr;
	hracoveAkcie = nullptr;

	sf::Sprite* logPozadie = new sf::Sprite();
	logHranice = new Tlacidlo(logPozadie, logPozadie, "", sf::Vector2f(0, 0), sf::Vector2f(300.f, okno->getSize().y-200.f), font, 35U);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {

			sf::Sprite* normalne = new sf::Sprite();
			tlacidla[i][j] = new Tlacidlo(normalne,normalne, "", sf::Vector2f(280.f + j * 50, okno->getSize().y - 200.f + 20.f + i * 50), sf::Vector2f(48, 48), font, 35U);
		}
	}


}


StavBoj::~StavBoj()
{
	delete logHranice;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			delete tlacidla[i][j];
		}
	}

}



void StavBoj::onEnter() {
	
	Stav::onEnter();
	if (boj == nullptr) {
		hra->zmenStavRozhrania("hranieHry");
	}
	else {
		hracoveAkcie = boj->Gethracovastatistika()->Getakcie();
		boj->bojStart();
	}
	

}





void StavBoj::onExit() {
	Stav::onExit();
}


void StavBoj::render() {
	

	sf::Sprite* nepriatelObrazok = boj->Getnepriatel()->Getobrazok();
	nepriatelObrazok->setPosition(sf::Vector2f(400.f, 100.f));
	nepriatelObrazok->setScale(1.5, 1.5);
	okno->draw(*nepriatelObrazok);

	okno->draw(*logHranice->Getsprite());
	sf::Text textLog(boj->Getlog(0, 40),*font,16U);
	textLog.setColor(sf::Color::White);
	textLog.setPosition(10, 10);

	if (textLog.getGlobalBounds().width > logHranice->getGlobalBounds().width - 20) {
		textLog.setScale(sf::Vector2f((logHranice->getGlobalBounds().width - 20) /textLog.getGlobalBounds().width, (textLog.getGlobalBounds().width - 20) / textLog.getGlobalBounds().width));
	}

	okno->draw(textLog);
	
	int i = 0;
	std::map<Efekt*,sf::Time>* aktivneEfekty = boj->Gethracovastatistika()->Getaktivneefekty();
	for (std::map<Efekt*, sf::Time>::iterator it = aktivneEfekty->begin(); it != aktivneEfekty->end(); ++it)
	{
		sf::Sprite* obrazok = it->first->Getobrazok();
		obrazok->setPosition(310.f + (obrazok->getGlobalBounds().width +3)*i, okno->getSize().y - obrazok->getGlobalBounds().height - 5.f-200.f);
		sf::Text trvanie(floattostring(-(boj->Getcasvboji().asSeconds() - it->second.asSeconds())),*font,13U);
		trvanie.setPosition(obrazok->getGlobalBounds().left, obrazok->getGlobalBounds().top + obrazok->getGlobalBounds().height - trvanie.getGlobalBounds().height-1);
		trvanie.setColor(sf::Color::White);
		okno->draw(*obrazok);
		okno->draw(trvanie);
		i++;
	}
	//npc efekty
	i = 0;
	aktivneEfekty = boj->Getnpcstatistika()->Getaktivneefekty();
	for (std::map<Efekt*, sf::Time>::iterator it = aktivneEfekty->begin(); it != aktivneEfekty->end(); ++it)
	{
		sf::Sprite* obrazok = it->first->Getobrazok();
		obrazok->setPosition(okno->getSize().x -10 - obrazok->getGlobalBounds().width , 80.f + (obrazok->getGlobalBounds().height + 3)*i);
		sf::Text trvanie(floattostring(-(boj->Getcasvboji().asSeconds() - it->second.asSeconds())), *font, 13U);
		trvanie.setPosition(obrazok->getGlobalBounds().left, obrazok->getGlobalBounds().top + obrazok->getGlobalBounds().height - trvanie.getGlobalBounds().height - 1);
		trvanie.setColor(sf::Color::White);
		okno->draw(*obrazok);
		okno->draw(trvanie);
		i++;
	}


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

	
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			unsigned int index = i * 9 + j;;

			okno->draw(*tlacidla[i][j]->Getsprite());
			if (index < hracoveAkcie->size()) {
				sf::Sprite* obrazok = hracoveAkcie->at(index)->Getobrazok();
				obrazok->setScale(1.5, 1.5);
				obrazok->setPosition(tlacidla[i][j]->getPosition().x, tlacidla[i][j]->getPosition().y);
				okno->draw(*obrazok);
			}
		}
	}


	// cerveny stvorec ktorý prekryje akciu ktorá sa nemoze vykonat
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(48, 48));
	rect.setFillColor(sf::Color(255, 0, 0, 128));
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			unsigned int index = i * 9 + j;
			if (index < hracoveAkcie->size()) {
				if (boj->maAkciaCooldown(hracoveAkcie->at(index))) {
					rect.setPosition(tlacidla[i][j]->getPosition().x, tlacidla[i][j]->getPosition().y);
					okno->draw(rect);
				}
			}
		}
	}

	//okno s infom predmetu
	sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			
			unsigned int index = i * 9 + j;
			if (tlacidla[i][j]->hover(pozicia) && index < hracoveAkcie->size()) {
				vykresliInfoAkcie(hracoveAkcie->at(index), tlacidla[i][j]->getPosition());
			}
		}
	}

	text.setColor(sf::Color::White);
	text.setString("Time:" + floattostring(boj->Getcasvboji().asSeconds()) + "");
	text.setPosition(sf::Vector2f(310, 10));
	okno->draw(text);



	//npc info
	int npcHp = boj->Getnpcstatistika()->Gethp();
	int npcMaxHp = boj->Getnpcstatistika()->GethpMax();
	int npcMp = boj->Getnpcstatistika()->Getmp();
	int npcMaxMp = boj->Getnpcstatistika()->GetmpMax();

	sf::RectangleShape npcHpBarZadny;
	npcHpBarZadny.setFillColor(sf::Color::White);
	npcHpBarZadny.setSize(sf::Vector2f(150.f, 35.f));
	npcHpBarZadny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 20.f));

	sf::RectangleShape npcHpBarPredny;
	npcHpBarPredny.setFillColor(sf::Color::Red);
	npcHpBarPredny.setSize(sf::Vector2f(((float)npcHp / npcMaxHp)*150.f, 35.f));
	npcHpBarPredny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 20.f));

	okno->draw(npcHpBarZadny);
	okno->draw(npcHpBarPredny);

	sf::RectangleShape npcMpBarZadny;
	npcMpBarZadny.setFillColor(sf::Color::White);
	npcMpBarZadny.setSize(sf::Vector2f(150.f, 35.f));
	npcMpBarZadny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 60.f));

	sf::RectangleShape npcMpBarPredny;
	npcMpBarPredny.setFillColor(sf::Color::Blue);
	npcMpBarPredny.setSize(sf::Vector2f(((float)npcMp / npcMaxMp)*150.f, 35));
	npcMpBarPredny.setPosition(sf::Vector2f(okno->getSize().x - 200.f, 60.f));

	okno->draw(npcMpBarZadny);
	okno->draw(npcMpBarPredny);

	//vykreslenie zivota a many npc vedla barov
	text.setString(std::to_string(npcHp) + "/" + std::to_string(npcMaxHp));
	text.setPosition(sf::Vector2f(npcHpBarZadny.getGlobalBounds().left - text.getGlobalBounds().width - 10, 25.f));
	okno->draw(text);
	text.setString(std::to_string(npcMp) + "/" + std::to_string(npcMaxMp));
	text.setPosition(sf::Vector2f(npcHpBarZadny.getGlobalBounds().left - text.getGlobalBounds().width - 10, 65.f));
	okno->draw(text);
	
	//cast bar

	sf::RectangleShape castPozadie;
	castPozadie.setFillColor(pozadieAkcie.getFillColor());
	castPozadie.setSize(sf::Vector2f(300, 65.f));
	castPozadie.setPosition(0.f, okno->getSize().y - pozadieAkcie.getSize().y - castPozadie.getSize().y);
	okno->draw(castPozadie);
	if (boj->castBarProgres() != -1) {
		
		sf::RectangleShape castZadny;
		castZadny.setFillColor(sf::Color::White);
		castZadny.setSize(sf::Vector2f(250, 35.f));
		castZadny.setPosition(sf::Vector2f(25, okno->getSize().y - pozadieAkcie.getSize().y - 50));

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
							unsigned int index = i * 9 + j;
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
	
		}
	}
}

void StavBoj::setBoj(Boj* paBoj) {
	if (boj != nullptr) {
		delete boj;
	}
	boj = paBoj;
}

void StavBoj::vykresliInfoAkcie(Akcia* akcia, sf::Vector2f pozicia) {

	sf::RectangleShape akciaInfo;
	akciaInfo.setFillColor(sf::Color::White);
	akciaInfo.setOutlineThickness(2);
	akciaInfo.setOutlineColor(sf::Color::Red);
	akciaInfo.setSize(sf::Vector2f(300, 180));
	akciaInfo.setPosition(pozicia.x +40, pozicia.y  - akciaInfo.getSize().y + 10);
	okno->draw(akciaInfo);

	sf::Text popisAkcie(akcia->Getmeno(), *font, 18U);
	popisAkcie.setColor(sf::Color::Black);
	popisAkcie.setPosition(akciaInfo.getGlobalBounds().left + 3, akciaInfo.getGlobalBounds().top + 3);
	okno->draw(popisAkcie);

	std::string popis = akcia->dajPopis() + "\n";

	if (akcia->Getcenamany() != 0) {
		popis += "Mana needed: " + std::to_string(akcia->Getcenamany()) + "\n";
	}

	if (dynamic_cast<AkciaDmg*>(akcia) != NULL) {
		AkciaDmg* dmgakcia = (AkciaDmg*)akcia;
		popis += "Damage:" + std::to_string(dmgakcia->minPoskodenie(boj->Gethracovastatistika())) + " - " + std::to_string(dmgakcia->maxPoskodenie(boj->Gethracovastatistika())) + "\n";
	}

	if (dynamic_cast<AkciaPoskodenieZbranou*>(akcia) != NULL) {
		AkciaPoskodenieZbranou* dmgakcia = (AkciaPoskodenieZbranou*)akcia;
		popis += "Damage:" + std::to_string(dmgakcia->minPoskodenie()) + " - " + std::to_string(dmgakcia->maxPoskodenie()) + "\n";
	}

	if (dynamic_cast<AkciaLiecenie*>(akcia) != NULL) {
		AkciaLiecenie* liecenieAkcia = (AkciaLiecenie*)akcia;
		popis += "Healing:" + std::to_string(liecenieAkcia->minLiecenie(boj->Gethracovastatistika())) + " - " + std::to_string(liecenieAkcia->maxLiecenie(boj->Gethracovastatistika())) + "\n";
	}


	if (dynamic_cast<AkciaPridanieEfektu*>(akcia) != NULL) {
		AkciaPridanieEfektu* efektAkcia = (AkciaPridanieEfektu*)akcia;
		popis += "Last: "+ floattostring(efektAkcia->Gettrvanie() / 1000.f)+" s\n";
	}

	if (akcia->GetcasCastenia() != 0) {
		popis += "Casting time:" + floattostring(akcia->GetcasCastenia()/1000.f) + " s\n";
	}
	if (akcia->Getcooldown() != 0) {
		popis += "Cooldown:" + floattostring(akcia->Getcooldown()/1000.f) + " s\n";
	}



	popisAkcie.setString(popis);
	popisAkcie.setCharacterSize(14);
	popisAkcie.setPosition(akciaInfo.getGlobalBounds().left + 3, akciaInfo.getGlobalBounds().top + 25);
	okno->draw(popisAkcie);

}


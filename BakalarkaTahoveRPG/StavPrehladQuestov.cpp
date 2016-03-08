#include "StavPrehladQuestov.h"
#include "Loader.h"
#include "QuestManager.h"
#include "Hrac.h"
#include "Quest.h"
#include "Hra.h"
#include "Tlacidlo.h"

#include <deque>

StavPrehladQuestov::StavPrehladQuestov(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra)
	:Stav(paNazov,paOkno,paHra)
{
	indexOd = 0;
	pocet = 12;

	dole.setRadius(30.f);
	dole.setPointCount(3);
	dole.setPosition(sf::Vector2f(340.f + dole.getGlobalBounds().width + 8, okno->getSize().y / 2 + 60.f));
	dole.rotate(180);

	hore.setRadius(30.f);
	hore.setPointCount(3);
	hore.setPosition(sf::Vector2f(340.f, okno->getSize().y / 2 - 60.f));

	sf::Texture textura;
	textura.create(50, 50);
	sf::Sprite* normalne = new sf::Sprite();
	sf::Sprite* zakliknute = new sf::Sprite(textura);
	zakliknute->setTextureRect(sf::IntRect(0, 0, 50, 300));
	zakliknute->setColor(sf::Color(255, 0, 0, 128));

	for (unsigned int i = 0; i < pocet; i++) {
		tlacidla.push_back(new Tlacidlo(normalne, zakliknute, "", sf::Vector2f(30.f,85.f+i*50), sf::Vector2f(300.f, 50.f), font, 35U));
	}

	tlacidloSpat = new Tlacidlo(normalne, normalne, "<--", sf::Vector2f(okno->getSize().x -60.f, 10.f), sf::Vector2f(45.f, 25.f), font, 20U);

}


StavPrehladQuestov::~StavPrehladQuestov()
{
}


void StavPrehladQuestov::onEnter() {
	spravcaQuestov = hra->GetHrac()->Getmanazerquestov();

	stlacenaKlavesa = true;
	stlacenaMys = true;
}

void StavPrehladQuestov::onExit() {

}

void StavPrehladQuestov::render() {

	sf::Text text("Prehlad Questov", *font, 45U);
	text.setPosition(sf::Vector2f(10.f, 10.f));
	okno->draw(text);

	sf::RectangleShape pozadieVolba;
	pozadieVolba.setFillColor(sf::Color::White);
	pozadieVolba.setSize(sf::Vector2f(300.f, 600));
	pozadieVolba.setPosition(sf::Vector2f(30.f, 85.f));
	okno->draw(pozadieVolba);

	float startX = 30.f;
	float startY = 85.f;

	for (unsigned int i = 0; i < pocet; i++)
	{
		okno->draw(*tlacidla[i]->Getsprite());
	}



	sf::Text nazov(" ", *font, 20U);
	nazov.setColor(sf::Color::Black);
	
	std::deque<Quest*> questy;
	
	std::deque<Quest*>* nedokoncene = spravcaQuestov->Getnedokoncenequesty();
	std::deque<Quest*>* dokoncene = spravcaQuestov->Getdokoncenequesty();

	for (unsigned int i = 0; i < nedokoncene->size(); i++) {
		questy.push_back(nedokoncene->at(i));
	}

	for (unsigned int i = 0; i < dokoncene->size(); i++) {
		questy.push_back(dokoncene->at(i));
	}

	for (unsigned int i = 0 ; i < questy.size(); i++) {
		if (i + indexOd >= questy.size()) {
			break;
		}
		nazov.setString(questy.at(i+indexOd)->Getnazov());

		if (text.getGlobalBounds().width > pozadieVolba.getGlobalBounds().width - 5) {
			text.setScale(sf::Vector2f((pozadieVolba.getGlobalBounds().width - 5) / text.getGlobalBounds().width, (pozadieVolba.getGlobalBounds().width - 5) / text.getGlobalBounds().width));
		}


		nazov.setPosition(sf::Vector2f(30.f,85.f+i*50.f));
		
		okno->draw(nazov);

	}


	okno->draw(hore);
	okno->draw(dole);

	sf::RectangleShape pozadieInfa;
	pozadieInfa.setFillColor(sf::Color::White);
	pozadieInfa.setSize(sf::Vector2f(550, 600));
	pozadieInfa.setPosition(sf::Vector2f(410.f,85.f));

	okno->draw(pozadieInfa);

	for (unsigned int i = 0; i < pocet; i++) {
		if (tlacidla.at(i+indexOd)->Getzakliknute()) {
			if (i + indexOd < questy.size()) {

				Quest* q = questy.at(i + indexOd);
				sf::Text info(q->Getnazov(), *font, 22);
				info.setColor(sf::Color::Red);
				info.setPosition(sf::Vector2f(pozadieInfa.getGlobalBounds().left+5.f,pozadieInfa.getGlobalBounds().top+5.f));
				okno->draw(info);
				info.move(sf::Vector2f(0,30.f));
				info.setColor(sf::Color::Black);
				info.setString(q->getPopis());
				info.setCharacterSize(13U);
				okno->draw(info);
			}
		}

	}


	okno->draw(*tlacidloSpat->Getsprite());
	sf::Text tt = tlacidloSpat->Gettext();
	tt.setColor(sf::Color::Yellow);
	okno->draw(tt);

	Stav::render();
}


void StavPrehladQuestov::update(double delta) {

	if (hra->maFocus()) {

		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
			{
				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);

				
				tlacidloSpat->skontrolujKlik(pozicia);
				if (tlacidloSpat->Getzakliknute()) {
					tlacidloSpat->Setzakliknute(false);
					hra->zmenStavRozhrania("hranieHry");
				}

				for (unsigned int i = 0; i < pocet; i++)
				{
					tlacidla[i]->skontrolujKlik(pozicia);
					//zrusenie zakliknutia ostatnych
					if (tlacidla[i]->Getzakliknute()) {
						for (unsigned int j = 0; j < pocet; j++)
						{
							if (i != j) {
								tlacidla.at(j)->Setzakliknute(false);
							}
						}
					}

				}


				if (hore.getGlobalBounds().intersects(sf::FloatRect(pozicia.x + 0.f,pozicia.y + 0.f,0.5f,0.5f))) { // kliknute na hore
					if (indexOd > 0) {
						indexOd--;
					}
					hore.setFillColor(sf::Color::Blue);

				}

				if (dole.getGlobalBounds().intersects(sf::FloatRect(pozicia.x+0.f, pozicia.y + 0.f, 0.5f, 0.5f))) { // kliknute na hore
					if (indexOd + pocet < spravcaQuestov->Getdokoncenequesty()->size() + spravcaQuestov->Getnedokoncenequesty()->size()) {
						indexOd++;
					}
					dole.setFillColor(sf::Color::Blue);
				}

				stlacenaMys = true;
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				stlacenaMys = false;
				hore.setFillColor(sf::Color::White);
				dole.setFillColor(sf::Color::White);
			}


			if (!stlacenaKlavesa && (sf::Keyboard::isKeyPressed(sf::Keyboard::O) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )) {
				hra->zmenStavRozhrania("hranieHry");
			}

			if (stlacenaKlavesa
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				stlacenaKlavesa = false;
			}
		
		}

	}


}
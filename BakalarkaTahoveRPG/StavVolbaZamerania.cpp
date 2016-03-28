#include "StavVolbaZamerania.h"
#include "Loader.h"
#include "Hra.h"
#include "Hrac.h"
#include "Zameranie.h"
#include "Nepriatel.h"
#include "AkciaPoskodenieZbranou.h"
#include "Tlacidlo.h"


StavVolbaZamerania::StavVolbaZamerania(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) : Stav(paNazov, paOkno, paHra) {
	oznacene = 0;
	scale = 0.0;
	const std::string cesta = "./Data/Grafika/";

	if (!rogueTextura.loadFromFile(cesta + "rogue.png", sf::IntRect(0, 0, 400, 400))) {

	}
	rogueObrazok.setTexture(rogueTextura);
	
	if (!warriorTextura.loadFromFile(cesta + "warrior.png", sf::IntRect(0, 0, 400, 400))) {

	}
	warriorObrazok.setTexture(warriorTextura);
	if (!mageTextura.loadFromFile(cesta + "mage.png", sf::IntRect(0, 0, 400, 400))) {

	}
	mageObrazok.setTexture(mageTextura);

	setnuteScale = false;

	sf::Texture texture;
	texture.create(1000, 1000);

	sf::Sprite* normalne = new sf::Sprite();
	normalne->setTexture(texture);
	normalne->setTextureRect(sf::IntRect(0, 0, 48, 48));
	normalne->setColor(sf::Color(0, 0, 0, 255));

	tlacidla[0] = new Tlacidlo(normalne, normalne, "", sf::Vector2f(0, 150), sf::Vector2f(500, 0), font, 85);
	tlacidla[1] = new Tlacidlo(normalne, normalne, "", sf::Vector2f(0, 260), sf::Vector2f(500, 0), font, 85);
	tlacidla[2] = new Tlacidlo(normalne, normalne, "", sf::Vector2f(0, 350), sf::Vector2f(500, 0), font, 85);
}



StavVolbaZamerania::~StavVolbaZamerania() {
	for (int i = 0; i < 3; i++) {
		delete tlacidla[i];
	}
}

void StavVolbaZamerania::onEnter() {
	Stav::onEnter();
	oznacene = 1;
    stlacenaKlavesa = true;
	
}


void StavVolbaZamerania::onExit() {
	Stav::onExit();
}


void StavVolbaZamerania::render() {
	
	int i = 60;
	sf::RectangleShape ukazovac;
	sf::Text nadpis("Choose your class:", *font, 40U);
	nadpis.setPosition(sf::Vector2f(okno->getSize().x / 2 - nadpis.getGlobalBounds().width / 2, 10.f));
	okno->draw(nadpis);


	ukazovac.setSize(sf::Vector2f(20.f+okno->getSize().x / 4, okno->getSize().y - 90.f));
	ukazovac.setFillColor(sf::Color::Yellow);
	ukazovac.setPosition(  i*oznacene -10.f + (oznacene-1)*(okno->getSize().x / 4.f)  , 90-10.f);
	okno->draw(ukazovac);
	
	sf::RectangleShape ramcek;
	sf::Text popis("", *font, 20);
	//warrior
	ramcek.setFillColor(sf::Color::Black);
	ramcek.setSize(sf::Vector2f(okno->getSize().x/4.f, okno->getSize().y - 115.f));
	ramcek.setPosition(i +0.f, 90.f);
	okno->draw(ramcek);

	nadpis.setString("Warrior");
	nadpis.setPosition(ramcek.getPosition().x + ramcek.getSize().x / 2 - nadpis.getGlobalBounds().width / 2, ramcek.getGlobalBounds().top);
	okno->draw(nadpis);

	if (!setnuteScale) {
		scale = ramcek.getSize().x / warriorObrazok.getGlobalBounds().width;
		warriorObrazok.setScale(scale, scale);
		mageObrazok.setScale(scale, scale);
		rogueObrazok.setScale(scale, scale);
		setnuteScale = true;
	}

	tlacidla[0]->Setpozicia(ramcek.getPosition());
	tlacidla[0]->setSize(ramcek.getSize());

	warriorObrazok.setPosition(ramcek.getPosition().x, nadpis.getGlobalBounds().top + nadpis.getGlobalBounds().height + 3);
	okno->draw(warriorObrazok);

	popis.setPosition(ramcek.getPosition().x + 3, warriorObrazok.getGlobalBounds().top + warriorObrazok.getGlobalBounds().height + 3);
	popis.setString("Clash your enemies with big\nsword dealing masive physical \ndamage to your enemies.\n\nWarriors have big health \nand great physical abilities.");
	okno->draw(popis);
	//mage

	ramcek.setSize(sf::Vector2f(okno->getSize().x / 4.f, okno->getSize().y - 115.f));
	ramcek.setPosition(i*2 + okno->getSize().x / 4.f, 90.f);
	okno->draw(ramcek);

	nadpis.setString("Mage");
	nadpis.setPosition(ramcek.getPosition().x + ramcek.getSize().x / 2 - nadpis.getGlobalBounds().width / 2, ramcek.getGlobalBounds().top);
	okno->draw(nadpis);

	mageObrazok.setPosition(ramcek.getPosition().x, nadpis.getGlobalBounds().top + nadpis.getGlobalBounds().height + 3);
	okno->draw(mageObrazok);

	tlacidla[1]->Setpozicia(ramcek.getPosition());
	tlacidla[1]->setSize(ramcek.getSize());

	popis.setPosition(ramcek.getPosition().x + 3, mageObrazok.getGlobalBounds().top + mageObrazok.getGlobalBounds().height + 3);
	popis.setString("Destroy your enemies with \npowerfull magic spells.\n\nMages have big intellect\nand great mana pool.\n");
	okno->draw(popis);

	//rogue


	ramcek.setSize(sf::Vector2f(okno->getSize().x / 4.f, okno->getSize().y -115.f));
	ramcek.setPosition(i*3 + 2*okno->getSize().x / 4.f,90.f);
	okno->draw(ramcek);

	nadpis.setString("Rogue");
	nadpis.setPosition(ramcek.getPosition().x + ramcek.getSize().x / 2 - nadpis.getGlobalBounds().width / 2, ramcek.getGlobalBounds().top);
	okno->draw(nadpis);

	rogueObrazok.setPosition(ramcek.getPosition().x, nadpis.getGlobalBounds().top + nadpis.getGlobalBounds().height + 3);
	okno->draw(rogueObrazok);

	tlacidla[2]->Setpozicia(ramcek.getPosition());
	tlacidla[2]->setSize(ramcek.getSize());

	popis.setPosition(ramcek.getPosition().x + 3, mageObrazok.getGlobalBounds().top + mageObrazok.getGlobalBounds().height + 3);
	popis.setString("Dance around your enemies \nwhile dealing huge amount \nof damage.\n\nRogues have great speed\nand big avoidance rate.\n");
	okno->draw(popis);

	Stav::render();
}


void StavVolbaZamerania::update(double delta) {
	if (hra->maFocus()) {

		Stav::update(delta);

		if (stav == StavAkcia::NORMAL) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == false)
			{
				sf::Vector2i pozicia = sf::Mouse::getPosition(*okno);
				for (unsigned int i = 0; i < 3; i++)
				{
					tlacidla[i]->skontrolujKlik(pozicia);
					if (tlacidla[i]->Getzakliknute()) {
						stlacenaMys = true;
						tlacidla[i]->Setzakliknute(false);
						zvoleneZameranie(i+1);

					}
				}
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && stlacenaMys == true) {
				stlacenaMys = false;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (oznacene > 1) {
					oznacene--;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				if (oznacene < 3) {
					oznacene++;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				hra->zmenStavRozhrania("hlavneMenu");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !stlacenaKlavesa) {
				stlacenaKlavesa = true;
				zvoleneZameranie(oznacene);

			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				stlacenaKlavesa = false;
			}
		}
	}
}


void StavVolbaZamerania::zvoleneZameranie(int paIndex) const
{
	Zameranie* zameranie;
	if (paIndex == 1) {
		zameranie = Loader::Instance()->nacitajZameranie("Warrior");
	}
	else if (paIndex == 2) {
		zameranie = Loader::Instance()->nacitajZameranie("Mage");
	}
	else {
		zameranie = Loader::Instance()->nacitajZameranie("Rogue");

	}

	Hrac* hrac = new Hrac(zameranie);
	hrac->Getstatistika()->vlozAkciu(new AkciaPoskodenieZbranou("Attack", "Attack with equipped weapon.", hrac->Getstatistika()));
	hra->SetHrac(hrac);

	Loader* loader = Loader::Instance();
	loader->nacitajMapu("prva", 14, 8, 2);
	hra->zmenStavRozhrania("hranieHry");
}

#include "StavCredits.h"
#include  "Hra.h"


StavCredits::StavCredits(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra) 
	:Stav(paNazov,paOkno,paHra)
{

}


StavCredits::~StavCredits()
{
}

void StavCredits::onEnter()
{
	stlacenaKlavesa = true;
	stlacenaMys = true;
}

void StavCredits::onExit()
{
}

void StavCredits::render()
{
	sf::Text text("Credits:",*font,85U);
	text.setPosition(okno->getSize().x / 2 - text.getGlobalBounds().width / 2, 10.f);
	okno->draw(text);
	text.setCharacterSize(50U);
	text.setString("Bachelor project made by Jakub Blunar.");
	text.setPosition(okno->getSize().x / 2 - text.getGlobalBounds().width / 2, 105.f);
	okno->draw(text);

	text.setString("Special thanks:");
	text.setPosition(20.f, 150.f);
	okno->draw(text);

	text.setCharacterSize(25U);
	text.setString("Web opengameart.org where I have found almost everything what I needed.\nWeb vxresource.wordpress.com for their great graphics. \nAvgvst - for his awensome music. \n\nMany artists from opengame art, whose graphics I am using. \n\nLanea Zimmerman, William Thompson, Tuomo Untinen, Manuel Riecke, Casper Nilsson,\nJohann CHARLOT,Robert Colladay, Stephen Challener, Charles Sanchez, Daniel Armstrong,\nJoshua Taylor, Barbara Rivera, Chris Phillips, Anamaris and Krusmira, Jonas Klinger,\nDaniel Eddeland and many more!");
	text.setPosition(20.f, 210.f);
	okno->draw(text);

	text.setCharacterSize(20U);
	text.setString("Press Esc or Left click to return...");
	text.setPosition(10.f,okno->getSize().y - 30.f);
	okno->draw(text);

	Stav::render();
}


void StavCredits::update()
{
	if (hra->maFocus()) {
		Stav::update();

		if (stav == StavAkcia::NORMAL) {
			if ((!stlacenaKlavesa && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (!stlacenaMys && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				hra->zmenStavRozhrania("hlavneMenu");
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				stlacenaMys = false;
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				stlacenaKlavesa = false;
			}
		}
	}
}

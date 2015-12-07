///////////////////////////////////////////////////////////
//  Hra.cpp
//  Implementation of the Class Hra
//  Created on:      05-12-2015 21:07:41
//  Original author: Jakub Blunár
///////////////////////////////////////////////////////////


#include "Hra.h"
#include "StavRozhrania.h"
#include "StavVolbaZamerania.h"
#include "StavHlavneMenu.h"

#define NAZOV "SUPERRPG"

Hra::Hra() {

	okno = new sf::RenderWindow(sf::VideoMode(1024, 768), NAZOV);
	okno->setFramerateLimit(60);

	std::string nazov = "hlavneMenu";
	Stav* stav1 = new StavHlavneMenu(nazov,okno,this);

	stavRozhraniaHry = new StavRozhrania(stav1);
	
	std::string nazov2 = "volbaZamerania";
	Stav* stav2 = new StavVolbaZamerania(nazov2,okno,this);
	stavRozhraniaHry->pridajStav(stav2);

	

}


Hra::~Hra() {
	delete(stavRozhraniaHry);
	delete(okno);
}


void Hra::start() {

	hlavnaSlucka();

}


void Hra::hlavnaSlucka() {
	
	while (okno->isOpen())
	{
		sf::Event event;

		while (okno->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno->close();
				
		}

		stavRozhraniaHry->update(20);
		okno->clear();
		stavRozhraniaHry->render(okno);
		okno->display();
	}

}

void Hra::zmenStavRozhrania(std::string paStav) {
	stavRozhraniaHry->zmenStav(paStav);
}
#include "Hra.h"

#include <random>
#include <time.h>
#include "Predmet.h"
#include "Generator.h"
#include  <iostream>

int main()
{
	srand((unsigned int)time(NULL));
	
	Generator* g = Generator::Instance();
	Predmet* p;
	for (int i = 0; i < 15; i++)
	{
		p = g->nahodnaZbran(5);
		std::cout << p->Getmeno() << " || " << p->Getsobrazok() << " || " << p->Getstringovytyp() << std::endl;
	}
	getchar();
	/*
	Hra* hra = new Hra();
	hra->start();*/
    return 0;
}


#pragma once
#if !defined(zbran_h)
#define zbran_h

#include "Pouzitelny.h"

class Zbran : public Pouzitelny
{

public:
	Zbran(std::string meno, int typ, std::string paObrazok, int cena, int paUroven,int paMinPoskodenie, int paMaxPoskodnie);
	virtual ~Zbran();

	int Getminposkodenie();
	int Getmaxposkodenie();

	void pouzi(Hrac* hrac);

private:
	int minPoskodenie;
	int maxPoskodenie;

};
#endif // !defined(EA_3E300562_0FCE_46c8_8500_484E316AD499__INCLUDED_)



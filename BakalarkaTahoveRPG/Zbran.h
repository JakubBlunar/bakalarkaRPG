#pragma once
#if !defined(zbran_h)
#define zbran_h

#include "Pouzitelny.h"


enum ZbranTyp {
ONEHAND_AXE = 0,
ONEHAND_SWORD = 1,
DAGGER = 2,
ONEHAND_MACE = 3,
TWOHAND_MACE = 4,
STAVE = 5,
POLEARM = 6,
TWOHAND_AXE = 7,
TWOHAND_SWORD = 8,
SHIELD = 9
};

class Zbran : public Pouzitelny
{

public:
	Zbran(std::string meno,int typ, std::string paObrazok, int cena, int paUroven,int paMinPoskodenie, int paMaxPoskodnie,int rychlostUtoku);
	virtual ~Zbran();

	int Getminposkodenie() const;
	int Getmaxposkodenie() const;
	int GetrychlostUtoku() const;
	void pouzi(Hrac* hrac) override;
	Zbran* copy() override;
private:
	int rychlostUtoku;
	int minPoskodenie;
	int maxPoskodenie;

};
#endif // !defined(EA_3E300562_0FCE_46c8_8500_484E316AD499__INCLUDED_)



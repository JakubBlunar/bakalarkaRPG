#pragma once
#include "Policko.h"

class Hrac;

class PolickoBoj: public Policko
{
public:
	PolickoBoj(bool paPriechodne);
	~PolickoBoj();

	void hracSkok(Hrac* paHrac);
private:
	bool jePopup;
	bool zapnute;
};


#pragma once

#if !defined(oblecenie_h)
#define oblecenie_h


#include <string>
#include "Pouzitelny.h"


class Oblecenie : public Pouzitelny
{

public:
	Oblecenie(std::string meno, int typ, std::string paObrazok, int cena, int paUroven);
	virtual ~Oblecenie();

	void pouzi(Hrac* hrac);

};
#endif
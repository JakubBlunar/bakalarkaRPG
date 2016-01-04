#pragma once

#if !defined(elixir_h)
#define elixir_h


#include <string>
#include "Pouzitelny.h"


class Elixir : public Pouzitelny
{

public:
	Elixir(std::string meno, int typ, std::string paObrazok, int cena, int paUroven, std::string zvysCo, int paoKolko);
	virtual ~Elixir();

	void pouzi(Hrac* hrac);
private:
	std::string stat;
	int oKolko;
};
#endif
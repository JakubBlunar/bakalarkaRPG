#pragma once

#if !defined(pouzitelny_h)
#define pouzitelny_h

#include "Predmet.h"

class Pouzitelny : public Predmet
{

public:
	int Getarmor();
	double GetarmorMult();
	int Gethp();
	int GethpMult();
	int Getinteligencia();
	double GetinteligenciaMult();
	int Getmp();
	int GetmpMult();
	int Getrychlost();
	double GetrychlostMult();
	int Getsila();
	double GetsilaMult();


	bool Isobleceny();


	void Setarmor(int newVal);
	void SetarmorMult(double newVal);
	void Sethp(int newVal);
	void SethpMult(int newVal);
	void Setinteligencia(int newVal);
	void SetinteligenciaMult(double newVal);
	void Setmp(int newVal);
	void SetmpMult(int newVal);
	void Setobleceny(bool newVal);
	void Setrychlost(int newVal);
	void SetrychlostMult(double newVal);
	void Setsila(int newVal);
	void SetsilaMult(double newVal);
protected:
	Pouzitelny(std::string meno, int typ, std::string paObrazok, int cena, int paUroven);
	virtual ~Pouzitelny();

private:
	int armor;
	double armorMult;
	int hp;
	int hpMult;
	int inteligencia;
	double inteligenciaMult;
	int mp;
	int mpMult;
	bool obleceny;
	int rychlost;
	double rychlostMult;
	int sila;
	double silaMult;

};
#endif

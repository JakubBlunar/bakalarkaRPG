#if !defined(pouzitelny_h)
#define pouzitelny_h

#include "Predmet.h"

/// <summary>
/// Zakladn· trieda , ktoru dedia predmety ktorÈ sa moûu obliecù
/// </summary>
class Pouzitelny : public Predmet
{

public:
	int Getarmor() const;
	double GetarmorMult() const;
	int Gethp() const;
	double GethpMult() const;
	int Getinteligencia() const;
	double GetinteligenciaMult() const;
	int Getmp() const;
	double GetmpMult() const;
	int Getrychlost() const;
	double GetrychlostMult() const;
	int Getsila() const;
	double GetsilaMult() const;

	/// <summary>
	/// Vrati true false ci je predmet oblecen˝
	/// </summary>
	/// <returns></returns>
	bool Isobleceny() const;

	void Setarmor(int newVal);
	void SetarmorMult(double newVal);
	void Sethp(int newVal);
	void SethpMult(double newVal);
	void Setinteligencia(int newVal);
	void SetinteligenciaMult(double newVal);
	void Setmp(int newVal);
	void SetmpMult(double newVal);
	void Setobleceny(bool newVal);
	void Setrychlost(int newVal);
	void SetrychlostMult(double newVal);
	void Setsila(int newVal);
	void SetsilaMult(double newVal);
protected:
	Pouzitelny(std::string meno, int typ, std::string paObrazok, int cena, int paUroven);
	virtual ~Pouzitelny();
	int armor;
	double armorMult;
	int hp;
	double hpMult;
	int inteligencia;
	double inteligenciaMult;
	int mp;
	double mpMult;
	bool obleceny;
	int rychlost;
	double rychlostMult;
	int sila;
	double silaMult;

};
#endif

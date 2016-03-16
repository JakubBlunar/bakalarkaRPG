#if !defined(Poziadavka_h)
#define Poziadavka_h

#include <string>

using namespace std;

class Nepriatel;
class Predmet;
class Hrac;

class Poziadavka
{
public:
	virtual void akcia(Nepriatel* nepriatel);
	virtual void akcia(string menoNepriatela);
	virtual void akcia(Predmet* predmet);
	virtual bool jeSplnena() = 0;
	virtual string Getpopis() = 0;
	virtual void dokoncenie(Hrac* paHrac);
};


class PoziadavkaZabi
	:public Poziadavka {

public:
	PoziadavkaZabi(std::string paKohoZabit, int paKolkokrat,string kde);
	void akcia(Nepriatel* paNepriatel);
	void akcia(string menoNepriatela);
	bool jeSplnena();
	string Getpopis();
	string Getkohozabit();
	int Getaktualnypocetzabitych();
	void Setpocetzabiti(int paPocet);
private:
	int kolkoZabit;
	string kohoZabit;
	int pocetZabiti;
	string menoMapy;
		
};



class PoziadavkaLoot
	:public Poziadavka {

public:
	PoziadavkaLoot(std::string paMenoPredmetu, int pocetKs);
	void akcia(Predmet* paPredmet);
	bool jeSplnena();
	string Getpopis();
private:
	int potrebneMnozstvo;
	std::string menoPredmetu;
	void dokoncenie(Hrac* paHrac);

};


#endif
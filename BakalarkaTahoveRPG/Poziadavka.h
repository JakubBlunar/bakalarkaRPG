#if !defined(Poziadavka_h)
#define Poziadavka_h

#include <string>

using namespace std;

class Nepriatel;
class Predmet;
class Hrac;

/// <summary>
/// Zakladna trieda poziadavky questu
/// </summary>
class Poziadavka
{
public:
	/// <summary>
	/// Akcia co spravi poziadavka ked hrac zabije nepriatela
	/// </summary>
	/// <param name="nepriatel">zabity nepriatel</param>
	virtual void akcia(Nepriatel* nepriatel);
	
	/// <summary>
	/// Akcia co spravi poziadavka ked hrac zabije nepriatela
	/// </summary>
	/// <param name="menoNepriatela">meno zabieho nepriatela</param>
	virtual void akcia(string menoNepriatela);

	/// <summary>
	/// akcia ktor· sa vykona ked hrac vezme predmet
	/// </summary>
	/// <param name="predmet">zobraty predmet</param>
	virtual void akcia(Predmet* predmet);

	/// <summary>
	/// Vrati ci je poziadavka splnen· alebo nie
	/// </summary>
	/// <returns>true, false</returns>
	virtual bool jeSplnena() = 0;

	/// <summary>
	/// Vrati popis poziadavky
	/// </summary>
	/// <returns>string popis poziadavky</returns>
	virtual string Getpopis() = 0;

	/// <summary>
	/// Poziadavka sa dokonci a vykona sa na dokonceni nejaka akcia podla poziadavky
	/// </summary>
	/// <param name="paHrac"></param>
	virtual void dokoncenie(Hrac* paHrac);
};

/// <summary>
/// Specifikacia poziadavky , kde hrac musÌ zabiù urciteho nepriatela urcity pocet x
/// </summary>
class PoziadavkaZabi
	:public Poziadavka {

public:

	/// <summary>
	/// Vytvori novu poziadavku na zabitie nepriatela a pocet kolko treba
	/// </summary>
	/// <param name="paKohoZabit">meno nepriatela</param>
	/// <param name="paKolkokrat">kolkokrat ho teraba zabiù</param>
	PoziadavkaZabi(std::string paKohoZabit, int paKolkokrat);

	/// <summary>
	/// Akcia co spravi poziadavka ked hrac zabije nepriatela
	/// </summary>
	/// <param name="nepriatel">zabity nepriatel</param>
	void akcia(Nepriatel* paNepriatel) override;
	
	/// <summary>
	/// Akcia co spravi poziadavka ked hrac zabije nepriatela
	/// </summary>
	/// <param name="menoNepriatela">meno zabieho nepriatela</param>
	void akcia(string menoNepriatela) override;

	/// <summary>
	/// Vrati ci je poziadavka splnen· alebo nie
	/// </summary>
	/// <returns>true, false</returns>
	bool jeSplnena() override;


	/// <summary>
	/// Vrati popis poziadavky
	/// </summary>
	/// <returns>string popis poziadavky</returns>
	string Getpopis() override;

	/// <summary>
	/// Vrati meno nepriatela ktorÈho treba zabit
	/// </summary>
	/// <returns>meno nepriatela</returns>
	string Getkohozabit() const;

	/// <summary>
	/// Vrati aktualny pocet zabit˝ch
	/// </summary>
	/// <returns>int pocet aktualne zabit˝ch</returns>
	int Getaktualnypocetzabitych() const;
	
	/// <summary>
	/// nastavi pocet aktualne zabit˝ch na zadanu hodnotu
	/// </summary>
	/// <param name="paPocet">nova hodnota</param>
	void Setpocetzabiti(int paPocet);
private:
	int kolkoZabit;
	string kohoZabit;
	int pocetZabiti;
		
};


/// <summary>
/// Specifikacia poziadavky, kde hrac musÌ nazbierat urcite mnozstvo predmetov
/// </summary>
class PoziadavkaLoot
	:public Poziadavka {

public:

	/// <summary>
	/// Vytvori novu poziadavku na nazbieranie urciteho mnozstva predmetov
	/// </summary>
	/// <param name="paMenoPredmetu">meno predmetu</param>
	/// <param name="pocetKs">kolko ich treba</param>
	PoziadavkaLoot(std::string paMenoPredmetu, int pocetKs);

	/// <summary>
	/// akcia ktor· sa vykona ked hrac vezme predmet
	/// </summary>
	/// <param name="predmet">zobraty predmet</param>
	void akcia(Predmet* paPredmet) override;

	/// <summary>
	/// Vrati ci je poziadavka splnen· alebo nie
	/// </summary>
	/// <returns>true, false</returns>
	bool jeSplnena() override;


	/// <summary>
	/// Vrati popis poziadavky
	/// </summary>
	/// <returns>string popis poziadavky</returns>
	string Getpopis() override;
private:
	int potrebneMnozstvo;
	std::string menoPredmetu;

	/// <summary>
	/// na dokonceni questu odstrani vöetky potrebne predmety z inventara
	/// </summary>
	/// <param name="paHrac"></param>
	void dokoncenie(Hrac* paHrac) override;

};


#endif
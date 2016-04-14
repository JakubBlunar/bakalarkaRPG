#if !defined(Policko_h)
#define Policko_h

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>

class Hrac;
class Vrstva;
class Npc;
class Predmet;

/// <summary>
/// Zakladna trieda policko ktor� reprezentuje jeden stvorcek na mape
/// </summary>
class Policko
{

public:
	/// <summary>
	/// Vytvor� nove policko a nastavi mu priechodnost podla parametra
	/// </summary>
	/// <param name="paPriechodne">ci je policko priechodne</param>
	Policko(bool paPriechodne);
	virtual ~Policko();

	/// <summary>
	/// Metoda ktor� sa spusti v�dy ked hr�� sko�� na pol��ko
	/// </summary>
	/// <param name="hrac">aktualny hrac</param>
	virtual void hracSkok(Hrac* hrac);

	/// <summary>
	/// Metoda ktor� sa vykona ked hr�� zvoli interakciu s poli�kom
	/// </summary>
	/// <param name="hrac"></param>
	void interakcia(Hrac* hrac);

	/// <summary>
	/// Vrati �i je dan� pol��ko priechodn�
	/// </summary>
	/// <returns>bool true, false</returns>
	bool jePrechodne() const;

	/// <summary>
	/// Nastavi texturu na indexe na zadanu texturu
	/// </summary>
	/// <param name="textura">ako ma vrsva vyzera�</param>
	/// <param name="poradie">poradie vrstvy</param>
	void nastavTexturu(sf::Texture* textura, int poradie);

	/// <summary>
	/// Nastavi priechodnost pol��ka
	/// </summary>
	/// <param name="paPriechodne">priechodnost true, false</param>
	void Setpriechodne(bool paPriechodne);

	/// <summary>
	/// Vr�ti obrazok vrstvy ktorej poradie ur�uje parameter
	/// </summary>
	/// <param name="poradie">index vrstvy</param>
	/// <returns></returns>
	sf::Sprite* dajObrazokVrstvy(int poradie);

	/// <summary>
	/// Postavi npc na pol�cko
	/// </summary>
	/// <param name="paNpc">konkretny npc</param>
	void Setnpc(Npc* paNpc);

	/// <summary>
	/// Vrati npc ktor� stoj� na pol��ku
	/// </summary>
	/// <returns>Npc npc</returns>
	Npc* Getnpc() const;

	/// <summary>
	/// Polozi urcity predmet na policko
	/// </summary>
	/// <param name="paPredmet">predmet</param>
	/// <param name="kedy">cas kedy ho hrac polozil</param>
	void polozPredmet(Predmet* paPredmet,sf::Time kedy);

	/// <summary>
	/// Vr�ti polozene predmety na policku
	/// </summary>
	/// <returns>vector polozene predmety</returns>
	std::vector<Predmet*>* dajPolozenePredmety() const;

	/// <summary>
	/// Vrati �i je na poli�ku polo�en� predmet
	/// </summary>
	/// <returns>true ak je polozeny , false nie je polozeny</returns>
	bool polozenyPredmet() const;

	/// <summary>
	/// Zmaze vsetky polozene predmety na policku
	/// </summary>
	void zmazPolozenePredmety();

	/// <summary>
	/// vrati cas kedy treba zamaza� predmety
	/// </summary>
	/// <returns></returns>
	float kedyZmazatPredmety() const;

protected:
	Npc* npc;
	std::vector<Predmet*>* polozenePredmety;
	bool priechodne;
	std::array<Vrstva*, 3> vrstvy;
	
	float casMazaniaPredmetov;

};

#endif
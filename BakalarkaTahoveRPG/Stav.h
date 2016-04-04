#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

class Hra;
class PopupOkno;
class Tlacidlo;

/// <summary>
/// Stav rozhrania, �o rob�
/// </summary>
enum StavAkcia {
	NORMAL,
	ZOBRAZUJE_POPUP,
	ZOBRAZUJE_LOOT
};

/// <summary>
/// Zakladn� trieda , ktor� rozhoduje �o sa bude vykreslova� na obrazovku
/// </summary>
class Stav
{

public:

	/// <summary>
	/// Vytvorenie noveho stavu
	/// </summary>
	/// <param name="paNazov">nazov stavu</param>
	/// <param name="paOkno">okno na ktor� vykresluje</param>
	/// <param name="paHra">hra</param>
	Stav(std::string paNazov, sf::RenderWindow* paOkno,Hra* paHra);
	virtual ~Stav();

	/// <summary>
	/// Aktualizovanie v�etkych potrebn�ch vec� , kontrola vstupu od hr��a
	/// </summary>
	virtual void update();

	/// <summary>
	/// Vykreslenie v�etkeho �o treba
	/// </summary>
	virtual void render();

	/// <summary>
	/// Nastavenie  premenn�ch , kontrola vstupn�ch podmienok do stavu
	/// </summary>
	virtual void onEnter();

	/// <summary>
	/// pri prep�nani zo stavu do ineho stavu sa tu vykonaju e�te posledn� veci
	/// </summary>
	virtual void onExit();

	/// <summary>
	/// Vr�ti nazov stavu
	/// </summary>
	/// <returns>string nazov stavu</returns>
	std::string Getnazov() const;

	/// <summary>
	/// Zobrazenie popup okna s informaciou pre hraca
	/// </summary>
	/// <param name="paCo">popup ktor� sa m� zobrazi�</param>
	void zobrazPopup(PopupOkno* paCo);

	/// <summary>
	/// Vr�ti �i stav akur�t zobrazuje popup alebo nie
	/// </summary>
	/// <returns>true ak zobrazuje , false ak nezobrazuje</returns>
	bool GetzobrazujePopup() const;

protected:
	StavAkcia stav;
	sf::Font* font;

	std::string nazov;
	sf::RenderWindow* okno;
	Hra* hra;

	std::deque<PopupOkno*> popupText;

	bool stlacenaKlavesa;
	bool stlacenaMys;

	Tlacidlo* popDalej;

	/// <summary>
	/// Sformatuje float na string s 2 desatinn�mi miestami
	/// </summary>
	/// <param name="cislo">desatinne cislo</param>
	/// <returns>string sformatovane cislo</returns>
	static std::string floattostring(float cislo);
};

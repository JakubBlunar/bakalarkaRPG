#ifndef tlacidlo_h
#define tlacidlo_h
#include "SFML\Graphics.hpp"

/// <summary>
/// Tlacidlo je objekt na obrazovke na ktorý moze hrac klikat
/// </summary>
class Tlacidlo {
public:
	/// <summary>
	/// Vytvori nove tlacidlo
	/// </summary>
	/// <param name="normal">obrazok ako vyzera normalne</param>
	/// <param name="clicked">obrazok ako vyzera zakliknute</param>
	/// <param name="text">text tlacidla</param>
	/// <param name="pozicia">pozicia tlacidla na obrazovke</param>
	/// <param name="velkost">velkost tlacidla</param>
	/// <param name="font">font textu na tlacidle</param>
	/// <param name="velkostPisma">velkost pisma na tlacidle</param>
	Tlacidlo(sf::Sprite* normal, sf::Sprite* clicked, std::string text, sf::Vector2f pozicia, sf::Vector2f velkost, sf::Font *font, unsigned int velkostPisma);
	~Tlacidlo();

	/// <summary>
	/// Skontroluje ci sa pozicia mysi trafila do tlacidla. ak ano nastavi tlacidlo na kliknute
	/// </summary>
	/// <param name="pozicia">pozicia</param>
	void skontrolujKlik(sf::Vector2i pozicia);

	/// <summary>
	/// Nastavi zakliknuté na danu hodnotu
	/// </summary>
	/// <param name="paNa">hodnota na ktoru zmenit</param>
	void Setzakliknute(bool paNa);

	/// <summary>
	/// Nastavi text tlacidla na dany text
	/// </summary>
	/// <param name="text">novy text tlacidla</param>
	void Settext(std::string text);

	/// <summary>
	/// Vrati ci je tlacidlo zakliknute alebo nie
	/// </summary>
	/// <returns>true ak je , false ak nie je </returns>
	bool Getzakliknute() const;

	/// <summary>
	/// Vrati obrazok tlacidla podla toho ci je zakliknute alebo nie
	/// </summary>
	/// <returns>obrazok tlacidla</returns>
	sf::Sprite* Getsprite() const;

	/// <summary>
	/// Vrati text tlacidla
	/// </summary>
	/// <returns>text tlacidla</returns>
	sf::Text Gettext();

	/// <summary>
	/// Skontroluje ci sa mys nenachadza nad tlacidlom
	/// </summary>
	/// <param name="pozicia">pozicia mysi</param>
	/// <returns>true ak ano , false ak nie</returns>
	bool hover(sf::Vector2i pozicia) const;

	/// <summary>
	/// Vrati poziciu tlacidla na obrazovke
	/// </summary>
	/// <returns>pozicia tlacidla</returns>
	sf::Vector2f getPosition() const;

	/// <summary>
	/// Vrati velkost tlacidla
	/// </summary>
	/// <returns>velkost tlacidla</returns>
	sf::Vector2f getSize() const;

	/// <summary>
	/// Vrati obdlznik ktorý predstavuje tlacidlo na obrazovke
	/// </summary>
	/// <returns>hranice tlacidla</returns>
	sf::FloatRect getGlobalBounds() const;

	/// <summary>
	/// Vrati Obdlznik , ktorý sa da vykreslit a je v tvare tlacidla
	/// </summary>
	/// <returns>obdlznik</returns>
	sf::RectangleShape Getramcek() const;

	/// <summary>
	/// Zmeni poziciu tlacidla
	/// </summary>
	/// <param name="paPozicia">nova pozicia</param>
	void Setpozicia(sf::Vector2f paPozicia);

	/// <summary>
	/// Nastavi velkost tlacidla na novu velkost
	/// </summary>
	/// <param name="paVelkost">nova velkost</param>
	void setSize(sf::Vector2f paVelkost);

private:
	sf::Sprite* normalne;
	sf::Sprite* kliknute;
	sf::Sprite* aktualne;
	sf::Text text;
	bool zakliknute;
	sf::Vector2f pozicia;
	sf::Vector2f velkost;
};
#endif
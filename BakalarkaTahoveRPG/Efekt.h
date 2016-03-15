#if !defined(Efekt_h)
#define Efekt_h

#include <SFML\Graphics.hpp>
#include <string>

class Statistika;

class Efekt
{
public:
	Efekt(std::string obrazok);
	virtual ~Efekt();
	virtual void aplikujSa(Statistika* paHrac) = 0;
	virtual void zrusUcinok(Statistika* statistika) = 0;
	virtual std::string popis() = 0;

	sf::Time GettrvanieDo();
	void setTrvanieDo(sf::Time paKoniec);
	sf::Sprite* Getobrazok();

	void Setstatistikanapocitanie(Statistika* statistika);

protected:
	sf::Time trvanieDo;

	sf::Texture textura;
	sf::Sprite* obrazok;
	Statistika* statistikaNaPocitanie;
};

#endif

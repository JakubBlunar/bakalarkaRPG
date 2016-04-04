#if !defined(StavVolbaZamerania_h)
#define StavVolbaZamerania_h

#include <vector>
#include "Stav.h"
#include <SFML\Graphics.hpp>

class Zameranie;

/// <summary>
/// Stav kde si hráè vyberie svoje Zameranie
/// </summary>
class StavVolbaZamerania : public Stav
{

public:
	StavVolbaZamerania(std::string paNazov,sf::RenderWindow* paOkno, Hra* paHra);
	virtual ~StavVolbaZamerania();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;
private:
	signed int oznacene;

	float scale;
	bool setnuteScale;

	Tlacidlo* tlacidla[3];

	sf::Texture warriorTextura;
	sf::Sprite warriorObrazok;

	sf::Texture mageTextura;
	sf::Sprite mageObrazok;

	sf::Texture rogueTextura;
	sf::Sprite rogueObrazok;

	/// <summary>
	/// Nacita zvolene zameranie , nacita mapu, hraca a spustí novu hru
	/// </summary>
	/// <param name="paIndex">volba zamerania od hraca</param>
	void zvoleneZameranie(int paIndex) const;
};

#endif
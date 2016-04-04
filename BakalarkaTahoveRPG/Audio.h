#if !defined(Audio_h)
#define Audio_h

#include "SFML/Audio.hpp"

/// <summary>
/// Predstavuje jeden nacitanı zvuk alebo pesnicku v pamäti. Pracuje z formatom ogg
/// </summary>
class Audio {
	sf::Music music;
	std::string subor;
	bool dobreNacitane;
public:
	Audio();

	/// <summary>
	/// Nacita zvuk na zdroji src , nastavi èi sa má opakova a nastaví hlasitos
	/// </summary>
	/// <param name="src">subor ktorı sa ma nacitat</param>
	/// <param name="loop">ci po skonceni prehravania sa pusti znovu</param>
	/// <param name="zakladneVolume">nastavenie hlasitosti</param>
	void init(std::string src, bool loop,float zakladneVolume);

	/// <summary>
	/// Ak je dobre nacitané tak spusti prehravanie hudby
	/// </summary>
	void play();

	/// <summary>
	/// Ak je dobre nacitané tak stopne prehravanie hudby
	/// </summary>
	void stop();

	/// <summary>
	/// Ak je dobre nacitané tak pausne prehrávanie hudby
	/// </summary>
	void pause();

	/// <summary>
	/// Vráti ci hudba hrá
	/// </summary>
	/// <returns>boolean ci hudba hra</returns>
	bool isPlaying() const;

	/// <summary>
	/// Vráti ci je hudba zastavená
	/// </summary>
	/// <returns>ci je hudba zastavena</returns>
	bool isStopped() const;

	/// <summary>
	/// Vrati ci je hudba pozastavena
	/// </summary>
	/// <returns>ci je hudba pozastavena</returns>
	bool isPaused() const;

	
};
#endif
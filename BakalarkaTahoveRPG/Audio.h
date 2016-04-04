#if !defined(Audio_h)
#define Audio_h

#include "SFML/Audio.hpp"

/// <summary>
/// Predstavuje jeden nacitan� zvuk alebo pesnicku v pam�ti. Pracuje z formatom ogg
/// </summary>
class Audio {
	sf::Music music;
	std::string subor;
	bool dobreNacitane;
public:
	Audio();

	/// <summary>
	/// Nacita zvuk na zdroji src , nastavi �i sa m� opakova� a nastav� hlasitos�
	/// </summary>
	/// <param name="src">subor ktor� sa ma nacitat</param>
	/// <param name="loop">ci po skonceni prehravania sa pusti znovu</param>
	/// <param name="zakladneVolume">nastavenie hlasitosti</param>
	void init(std::string src, bool loop,float zakladneVolume);

	/// <summary>
	/// Ak je dobre nacitan� tak spusti prehravanie hudby
	/// </summary>
	void play();

	/// <summary>
	/// Ak je dobre nacitan� tak stopne prehravanie hudby
	/// </summary>
	void stop();

	/// <summary>
	/// Ak je dobre nacitan� tak pausne prehr�vanie hudby
	/// </summary>
	void pause();

	/// <summary>
	/// Vr�ti ci hudba hr�
	/// </summary>
	/// <returns>boolean ci hudba hra</returns>
	bool isPlaying() const;

	/// <summary>
	/// Vr�ti ci je hudba zastaven�
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
#if !defined(AudioManager_h)
#define AudioManager_h

#include <string>
#include <map>

using namespace std;

class Audio;

/// <summary>
/// Trieda ktor· ma na starosti nacitavanie a prehravanie hudby
/// Singleton
/// </summary>
class AudioManager
{
public:
	/// <summary>
	/// Staticka metoda , sluzi ako konstruktor
	/// </summary>
	/// <returns>Instancia</returns>
	static AudioManager* Instance();

	/// <summary>
	/// Nacita zvukov˝ subor vo formate ogg a ulozi ho do nacitan˝ch efektov
	/// </summary>
	/// <param name="src">subor na otvorenie</param>
	/// <param name="volume">hlasitosù ktor· sa mu nastavÌ</param>
	void nacitajEfekt(string src,float volume);


	/// <summary>
	/// Nacita zvukov˝ subor vo formate ogg a ulozi ho do nacitanej hudby
	/// </summary>
	/// <param name="src">subor na otvorenie</param>
	/// <param name="volume">hlasitosù ktor· sa mu nastavÌ</param>
	void nacitajHudbu(string src,float volume);

	/// <summary>
	/// Vrati hudbu ktorej nazov je src
	/// </summary>
	/// <param name="src">nazov suboru hudby</param>
	/// <returns></returns>
	Audio* dajHudbu(string src);

	/// <summary>
	/// Vrati efekt ktoreho nazov je src
	/// </summary>
	/// <param name="src">nazov suboru efektu</param>
	/// <returns></returns>
	Audio* dajEfekt(string src);

	/// <summary>
	/// Prehra efekt ktoreho nazov je src
	/// </summary>
	/// <param name="src">nazov suboru efektu</param>
	void playEfekt(string src);

	/// <summary>
	/// D· nahodnu hudbu z nacitanej hudby
	/// </summary>
	/// <returns>Audio hudba</returns>
	Audio* dajNahodnuHudbu();
private:

	/// <summary>
	/// Vytvori nov˝ Audiomanager
	/// </summary>
	AudioManager() {};

	AudioManager(AudioManager const&) {};
	AudioManager& operator=(AudioManager const&) const
	{
		return *instancia;
	};
	static AudioManager* instancia;

	map<string, Audio*> efekty;
	map<string, Audio*> hudba;
	

};

#endif
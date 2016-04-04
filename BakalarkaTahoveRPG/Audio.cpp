#include "Audio.h"

Audio::Audio()
{
	dobreNacitane = false;
}

void Audio::init(std::string src, bool loop, float zakladneVolume)
{
	const std::string cesta = "./Data/Zvuky/";
	dobreNacitane = false;
	subor = src;
	
	if (music.openFromFile(cesta + src)){
		dobreNacitane = true;
		music.setLoop(loop);
		music.setVolume(zakladneVolume);
	}
	else
	{
		dobreNacitane = false;
	}

}

void Audio::play() {
	if (dobreNacitane && music.getStatus() != sf::Music::Playing) {
		music.play();
	}
	
}
void Audio::stop() {
	if (dobreNacitane) {
		music.stop();
	}
}

void Audio::pause()
{
	if(dobreNacitane)
	{
		music.pause();
	}
}

bool Audio::isPlaying() const
{
	if (dobreNacitane) {
		return music.getStatus() == sf::Music::Playing;
	}
	return false;
}

bool Audio::isStopped() const
{
	if (dobreNacitane) {
		return music.getStatus() == sf::Music::Stopped;
	}
	return false;
}

bool Audio::isPaused() const
{
	if (dobreNacitane) {
		return music.getStatus() == sf::Music::Paused;
	}
	return false;
}

#include "AudioManager.h"

#include <random>
#include <ctime>

#include "Audio.h"

AudioManager* AudioManager::instancia = nullptr;

AudioManager* AudioManager::Instance()
{
	if (!instancia) {
		srand(static_cast<unsigned int>(time(NULL)));
		instancia = new AudioManager();
	}
	return instancia;
}

void AudioManager::nacitajEfekt(string src,float volume)
{
	if(efekty.find(src) == efekty.end())
	{
		Audio* a = new Audio();
		a->init(src, false, volume);
		efekty.insert_or_assign(src, a);
	}
}

void AudioManager::nacitajHudbu(string src, float volume)
{
	if (hudba.find(src) == hudba.end())
	{
		Audio* a = new Audio();
		a->init(src, false, volume);
		hudba.insert_or_assign(src, a);
	}
}

Audio* AudioManager::dajHudbu(string src)
{	
	try {
		return hudba.at(src);
	}catch(...)
	{
		return nullptr;
	}
}

Audio* AudioManager::dajEfekt(string src)
{
	try {
		return efekty.at(src);
	}
	catch (...)
	{
		return nullptr;
	}
}

void AudioManager::playEfekt(string src)
{
	try {
		efekty.at(src+".ogg")->play();
	}
	catch (...)
	{
		
	}
}

Audio* AudioManager::dajNahodnuHudbu()
{
	if (hudba.size() > 0) {
		auto it = hudba.begin();
		std::advance(it, rand() % hudba.size());
		string k = it->first;

		return hudba.at(k);
	}
	return nullptr;
}

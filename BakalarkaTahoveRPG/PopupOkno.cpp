#include "PopupOkno.h"



PopupOkno::PopupOkno(std::string paText)
{
	texty.push(paText);
	koniec = false;
}


PopupOkno::~PopupOkno()
{
}

bool PopupOkno::skoncil() {
	return (texty.size() > 1) ? false :true;
}

std::string PopupOkno::aktualnaStrana() {
	if (texty.size() > 0) {
		std::string vratene = texty.front();
		return vratene;
	}
	return "";
}

std::string PopupOkno::dajDalsi() {
	if (texty.size() > 0) {
		std::string vratene = texty.front();
		texty.pop();
		return vratene;
	}
	return "";
}

void PopupOkno::pridajStranku(std::string paText) {
	texty.push(paText);
}
#include "PopupOkno.h"



PopupOkno::PopupOkno(string paText)
{
	texty.push(paText);
	koniec = false;
}


PopupOkno::~PopupOkno()
{
}

bool PopupOkno::skoncil() const
{
	return (texty.size() > 1) ? false :true;
}

string PopupOkno::aktualnaStrana() {
	if (texty.size() > 0) {
		string vratene = texty.front();
		return vratene;
	}
	return "";
}

string PopupOkno::dajDalsi() {
	if (texty.size() > 0) {
		string vratene = texty.front();
		texty.pop();
		return vratene;
	}
	return "";
}

void PopupOkno::pridajStranku(string paText) {
	texty.push(paText);
}
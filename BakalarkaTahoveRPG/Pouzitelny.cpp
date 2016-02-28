#include "Pouzitelny.h"


Pouzitelny::Pouzitelny(std::string meno, int typ, std::string paObrazok, int cena, int paUroven) :Predmet(meno,typ,paObrazok,cena,paUroven){
	obleceny = false;
	hp = 0;
	hpMult = 0;
	mp = 0;
	mpMult = 0;
	sila = 0;
	silaMult = 0;
	rychlost = 0;
	rychlostMult = 0;
	inteligencia = 0;
	inteligenciaMult = 0;
	armor = 0;
	armorMult = 0;

}



Pouzitelny::~Pouzitelny() {
}





int Pouzitelny::Getarmor() {

	return armor;
}


double Pouzitelny::GetarmorMult() {

	return armorMult;
}


int Pouzitelny::Gethp() {

	return hp;
}


double Pouzitelny::GethpMult() {

	return hpMult;
}


int Pouzitelny::Getinteligencia() {

	return inteligencia;
}


double Pouzitelny::GetinteligenciaMult() {

	return inteligenciaMult;
}


int Pouzitelny::Getmp() {

	return mp;
}


double Pouzitelny::GetmpMult() {

	return mpMult;
}


int Pouzitelny::Getrychlost() {

	return rychlost;
}


double Pouzitelny::GetrychlostMult() {

	return rychlostMult;
}


int Pouzitelny::Getsila() {

	return sila;
}


double Pouzitelny::GetsilaMult() {

	return silaMult;
}


bool Pouzitelny::Isobleceny() {

	return obleceny;
}


void Pouzitelny::Setarmor(int newVal) {

	armor = newVal;
}


void Pouzitelny::SetarmorMult(double newVal) {

	armorMult = newVal;
}


void Pouzitelny::Sethp(int newVal) {

	hp = newVal;
}


void Pouzitelny::SethpMult(double newVal) {

	hpMult = newVal;
}


void Pouzitelny::Setinteligencia(int newVal) {

	inteligencia = newVal;
}


void Pouzitelny::SetinteligenciaMult(double newVal) {

	inteligenciaMult = newVal;
}


void Pouzitelny::Setmp(int newVal) {

	mp = newVal;
}


void Pouzitelny::SetmpMult(double newVal) {

	mpMult = newVal;
}


void Pouzitelny::Setobleceny(bool newVal) {

	obleceny = newVal;
}


void Pouzitelny::Setrychlost(int newVal) {

	rychlost = newVal;
}


void Pouzitelny::SetrychlostMult(double newVal) {

	rychlostMult = newVal;
}


void Pouzitelny::Setsila(int newVal) {

	sila = newVal;
}


void Pouzitelny::SetsilaMult(double newVal) {

	silaMult = newVal;
}
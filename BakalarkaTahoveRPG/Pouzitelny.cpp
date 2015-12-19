#include "Pouzitelny.h"


Pouzitelny::Pouzitelny(std::string meno, int typ, std::string paObrazok, int cena) :Predmet(meno,typ,paObrazok,cena){
	obleceny = false;
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


int Pouzitelny::GethpMult() {

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


int Pouzitelny::GetmpMult() {

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


void Pouzitelny::SethpMult(int newVal) {

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


void Pouzitelny::SetmpMult(int newVal) {

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
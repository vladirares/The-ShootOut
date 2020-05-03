#include "CeramicArmor.h"

CeramicArmor::CeramicArmor(const char* texturesheet, SDL_Renderer* ren, int x, int y) :Armor(texturesheet, ren, x, y) {
	this->baseDamageAbsorption = 0.3f;
	this->bulletDamageAbsorption = 0.8f;
	this->slashDamageAbsorption = 0.7f;
	this->explosionDamageAbsorption = 0.4f;
	this->hp = 100;
	this->weight = 0.4f;
	this->name = "CeramicArmor";
}

int CeramicArmor::calculateTotalDamage(Weapon &arma) {
	int totalDamage = 0;
	totalDamage += arma.getDamage().baseDamage * (1 - baseDamageAbsorption * hp/100) ;
	totalDamage += arma.getDamage().bulletDamage * (1 - bulletDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().slashDamage * (1 - slashDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().explosionDamage * (1 - explosionDamageAbsorption * hp / 100);
	return totalDamage;
}

CeramicArmor::~CeramicArmor() {

}
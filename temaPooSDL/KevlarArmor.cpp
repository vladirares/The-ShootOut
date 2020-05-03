#include "KevlarArmor.h"

KevlarArmor::KevlarArmor(const char* texturesheet, SDL_Renderer* ren, int x, int y) :Armor(texturesheet, ren, x, y) {
	this->baseDamageAbsorption = 0.1f;
	this->bulletDamageAbsorption = 0.5f;
	this->slashDamageAbsorption = 0.2f;
	this->explosionDamageAbsorption = 0.1f;
	this->name = "KevlarArmor";
	this->hp = 100;
	this->weight = 0.2f;
}

int KevlarArmor::calculateTotalDamage(Weapon &arma) {
	int totalDamage = 0;
	totalDamage += arma.getDamage().baseDamage * (1 - baseDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().bulletDamage * (1 - bulletDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().slashDamage * (1 - slashDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().explosionDamage * (1 - explosionDamageAbsorption * hp / 100);
	return totalDamage;
}

KevlarArmor::~KevlarArmor() {

}
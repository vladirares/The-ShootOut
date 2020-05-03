#include "JuggernautArmor.h"

JuggernautArmor::JuggernautArmor(const char* texturesheet, SDL_Renderer* ren, int x, int y) :Armor(texturesheet, ren, x, y) {
	this->baseDamageAbsorption = 0.6f;
	this->bulletDamageAbsorption = 0.4f;
	this->slashDamageAbsorption = 0.5f;
	this->explosionDamageAbsorption = 0.8f;
	this->name = "JuggernautArmor";
	this->hp = 100;
	this->weight = 0.8f;

}

int JuggernautArmor::calculateTotalDamage(Weapon& arma) {
	int totalDamage = 0;
	totalDamage += arma.getDamage().baseDamage * (1 - baseDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().bulletDamage * (1 - bulletDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().slashDamage * (1 - slashDamageAbsorption * hp / 100);
	totalDamage += arma.getDamage().explosionDamage * (1 - explosionDamageAbsorption * hp / 100);
	return totalDamage;
}

JuggernautArmor::~JuggernautArmor() {

}
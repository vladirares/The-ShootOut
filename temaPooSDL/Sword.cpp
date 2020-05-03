#include "Sword.h"

Sword::Sword(const char* texturesheet, SDL_Renderer* ren, int x, int y) : Weapon(texturesheet, ren, x, y) {
	this->damage.baseDamage = 20;
	this->damage.bulletDamage = 0;
	this->damage.explosionDamage = 0;
	this->damage.slashDamage = 120;
	this->name = "sword";
}

Sword::~Sword() {

}
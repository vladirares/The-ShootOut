#include "Bazooka.h"

Bazooka::Bazooka(const char* texturesheet, SDL_Renderer* ren, int x, int y) : Weapon(texturesheet, ren, x, y) {
	this->damage.baseDamage = 20;
	this->damage.bulletDamage = 20;
	this->damage.explosionDamage = 150;
	this->damage.slashDamage = 0;
	this->name = "bazooka";
}


Bazooka::~Bazooka() {

}

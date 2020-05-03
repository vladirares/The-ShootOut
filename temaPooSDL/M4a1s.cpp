#include "M4a1s.h"

M4a1s::M4a1s(const char* texturesheet, SDL_Renderer* ren, int x, int y) : Weapon (texturesheet, ren, x, y) {
	this->damage.baseDamage = 10;
	this->damage.bulletDamage = 100;
	this->damage.explosionDamage = 10;
	this->damage.slashDamage = 0;
	this->name = "m4a1s";
}


M4a1s::~M4a1s() {

}

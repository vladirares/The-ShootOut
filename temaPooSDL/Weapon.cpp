#include "Weapon.h"

Weapon::Weapon(const char* texturesheet, SDL_Renderer* ren, int x, int y) :GameObject(texturesheet, ren, x, y) {

}

Weapon::Damage Weapon::getDamage() {
	return damage;
}

void Weapon::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void Weapon::Update(int x, int y) {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

string Weapon::getName() {
	return name;
}

Weapon::~Weapon() {

}

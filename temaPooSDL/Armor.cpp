#include "Armor.h"
Armor::Armor(const char* texturesheet, SDL_Renderer* ren, int x, int y) :GameObject(texturesheet, ren, x, y) {
	
}

void Armor::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void Armor::Update(int x,int y) {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

string Armor::getName() {
	return name;
}

void Armor::setHp(int val) {
	this->hp = val;
}

float Armor::getWeight() {
	return weight;
}

int	Armor::getHp() {
	return hp;
}


Armor::~Armor() {

}

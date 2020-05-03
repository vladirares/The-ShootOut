#pragma once
#include "Weapon.h"
class Sword : public Weapon
{
public:
	Sword(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~Sword();
};


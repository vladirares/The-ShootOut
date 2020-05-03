#pragma once
#include "Weapon.h"
class Bazooka : public Weapon
{
public:
	Bazooka(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~Bazooka();
};


#pragma once
#include "Weapon.h"
class M4a1s : public Weapon
{
public:
	M4a1s(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~M4a1s();
};


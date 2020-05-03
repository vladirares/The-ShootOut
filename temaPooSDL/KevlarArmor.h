#pragma once
#include"Armor.h"
#include"GameObject.h"

class KevlarArmor : public Armor
{
public:
	KevlarArmor(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	int calculateTotalDamage(Weapon&);
	~KevlarArmor();
};


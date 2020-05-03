#pragma once
#include "Armor.h"
class JuggernautArmor : public Armor
{
public:
	JuggernautArmor(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	int calculateTotalDamage(Weapon&);
	~JuggernautArmor();
};


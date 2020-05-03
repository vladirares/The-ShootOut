#pragma once
#include"Armor.h"
#include"GameObject.h"
class CeramicArmor : public Armor
{
	
public:
	CeramicArmor(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	int calculateTotalDamage(Weapon&);
	
	~CeramicArmor();
};


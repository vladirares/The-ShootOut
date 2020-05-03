#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include <string>
using namespace std;
class Armor : public GameObject
{
protected:

	float baseDamageAbsorption;
	float bulletDamageAbsorption;
	float slashDamageAbsorption;
	float explosionDamageAbsorption;
	int hp;
	float weight;
	string name;

public:

	Armor(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	virtual int calculateTotalDamage(Weapon&) = 0;
	void Render();
	void Update(int,int);
	int getHp();
	void setHp(int);
	float getWeight();
	string getName();
	virtual ~Armor();
};


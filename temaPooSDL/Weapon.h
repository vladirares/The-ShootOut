#pragma once
#include<string>
#include"GameObject.h"
using namespace std;
class Weapon : public GameObject
{
protected:
	struct Damage {
		int baseDamage;
		int bulletDamage;
		int slashDamage;
		int explosionDamage;
	};
	string name;
	Damage damage;

public:
	Weapon(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	void Render();
	void Update(int,int);
	Damage getDamage();
	string getName();
	virtual ~Weapon();
};


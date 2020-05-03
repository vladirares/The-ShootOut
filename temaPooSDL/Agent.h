#pragma once
#include"GameObject.h"
#include"Bloc.h"
#include"Map.h"
#include<vector>
#include"Armor.h"
#include"KevlarArmor.h"
#include"CeramicArmor.h"
#include"Weapon.h"
#include"M4a1s.h"
#include"Sword.h"
#include"Bazooka.h"
#include"JuggernautArmor.h"
using namespace std;


class Agent: public GameObject
{
	int id;
	int hp;
	int visibilityArea;
	int xCoord, yCoord;
	Armor* armor;
	Weapon* weapon;
	vector<int> enemies;
	SDL_Rect srcRectVisibility, destRectVisibility;
	SDL_Texture* visibilityTexture;
public:
	Agent(const char* texturesheet, const char* visibTexture,SDL_Renderer* ren, int x, int y);
	void setId(int);
	void setArmor(Armor*);
	void setWeapon(Weapon*);
	void setVisibilityArea(int);
	void setXCoord(int);
	void setYCoord(int);
	void attack(vector<Agent*>);
	void takeDamage(int,vector<Agent*>);
	void move(Map &);
	void takeAction(Map &,vector<Agent*>);
	int getId();
	int getXCoord();
	int getYCoord();
	int getHp();
	vector<int> getEnemies();
	void Render();
	void Update();
	int getVisibilityArea();

};



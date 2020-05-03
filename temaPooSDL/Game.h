#pragma once
#include "SDL.h"
#include "Map.h"
#include "ObjectManager.h"
#include "Armor.h"
#include "KevlarArmor.h"
#include "CeramicArmor.h"
#include "Weapon.h"
#include "M4a1s.h"
#include "Sword.h"
#include "Bazooka.h"
#include "JuggernautArmor.h"
#include<iostream>
class Game
{
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	static Map* map;
	static ObjectManager objects;
	int cnt = 0;
public:
	Game();
	~Game();
	static Map* getMap();
	void init(const char* title, int xpos, int ypos, int width, int height, int noAgents, int visibilityArea, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();

};


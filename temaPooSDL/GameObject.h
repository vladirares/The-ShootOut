#pragma once
#include "TextureManager.h"

class GameObject
{
protected:
	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
public:
	GameObject(const char* texturesheet, SDL_Renderer* ren,int x, int y);
	virtual ~GameObject();
	void Update();
	void Render();

};


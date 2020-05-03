#pragma once
#include "SDL_image.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static void Draw(SDL_Renderer* ren,SDL_Texture *tex, SDL_Rect src, SDL_Rect dest );
};


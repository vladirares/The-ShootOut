#pragma once
#include <vector>
#include"GameObject.h"
//#include"Agent.h"
#include "Bloc.h"
#include <time.h> 

class Map
{
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;

	vector< vector<Bloc> > blocuri;
	int noAgents;
	int noBlocksX;
	int noBlocksY;


public:
	vector< vector<Bloc> >& getBlocuri();
	void setHarta(int, int, int);
	//void refresh();
	Map(SDL_Renderer* ren,int x=25 ,int y =25,int noAgents=2);
	friend ostream& operator << (ostream& out,const Map&);
	bool haveWinner();
	~Map();

	void DrawMap(SDL_Renderer* ren);
};


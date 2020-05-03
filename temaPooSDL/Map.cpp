#include "Map.h"


vector< vector<Bloc> >& Map::getBlocuri() {
	return blocuri;
}

void Map::setHarta(int noBlocksX = 25, int noBlocksY = 25, int noAgents = 4) {
	this->noAgents = noAgents;
	this->noBlocksX = noBlocksX;
	this->noBlocksY = noBlocksY;
	this->blocuri.resize(noBlocksY);
	for (int i = 0; i < noBlocksY; i++) {
		this->blocuri[i].resize(noBlocksX);
	}

	srand(time(NULL));

	for (int i = 0; i < noBlocksY; i++) {
		for (int j = 0; j < noBlocksX; j++) {
			int tip = rand() % 2;
			blocuri[i][j].setType(tip);
			blocuri[i][j].setIsOccupied(false);
		}
	}
}

Map::Map(SDL_Renderer* ren, int noBlocksX , int noBlocksY,int noAgents ) {
	dirt = TextureManager::LoadTexture("assets/dirt.png", ren);
	grass = TextureManager::LoadTexture("assets/grass.png", ren);
	this->setHarta(noBlocksX,noBlocksY,noAgents);
	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;
	dest.x = dest.y = 0;
}

ostream& operator<<(ostream& out, const Map& map) {
	for (int i = 0; i < map.blocuri.size(); i++) {
		for (int j = 0; j < map.blocuri[0].size(); j++) {
			out << map.blocuri[i][j].getAgentId() << " ";
		}
		out << endl;
	}
	return out;
}

bool Map::haveWinner() {
	int total = 0;
	int id = 0;
	for (int i = 0; i < blocuri.size(); i++) {
		for (int j = 0; j < blocuri[0].size(); j++) {
			if (blocuri[i][j].isOccupied()) {
				total++;
				id = blocuri[i][j].getAgentId();
			}
		}
	}
	if (total == 1) {
		cout << endl << "The winner is " << id << endl;
		return true;
	}
	if (total == 0) {
		cout << endl << "Nobody won" << endl;
		return true;
	}
	return false;
}

void Map::DrawMap(SDL_Renderer* ren) {
	int type = 0;

	for (int row = 0; row < noBlocksY; row++) {
		for (int column = 0; column < noBlocksX; column++) {
			type = blocuri[row][column].getType();
			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			case 0:
				TextureManager::Draw(ren, dirt, src, dest);
				break;
			case 1:
				TextureManager::Draw(ren, grass, src, dest);
				break;
			default:
				break;
			}
		}
	}
}
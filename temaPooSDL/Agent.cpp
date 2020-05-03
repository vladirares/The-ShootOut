#include "Agent.h"

Agent::Agent(const char* texturesheet,const char* visibTexture, SDL_Renderer* ren, int x, int y) :GameObject( texturesheet, ren, x, y) {
	visibilityTexture = TextureManager::LoadTexture(visibTexture, ren);
	this->hp = 100;
}

void Agent::setId(int id){
	this->id = id;
}

void Agent::setArmor(Armor* armor) {
	this->armor = armor;
}

void Agent::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}

void Agent::setXCoord(int x) {
	this->xCoord = x;
}

void Agent::setYCoord(int y) {
	this->yCoord = y;
}

void Agent::setVisibilityArea(int area) {
	this->visibilityArea = area;
}

int Agent::getVisibilityArea(){
	return visibilityArea;
}

int Agent::getXCoord() {
	return xCoord;
}

void Agent::takeAction(Map &harta,vector<Agent*>Agents) {
	int iMin,iMax,jMin,jMax;
	vector<vector<Bloc> > map = harta.getBlocuri();
	vector<int> enemiesEncountered;
	
	if (getXCoord() - getVisibilityArea()/2 < 0) {
		jMin = 0;
	}
	else {
		jMin = getXCoord() - getVisibilityArea()/2;
	}
	if (getXCoord() + getVisibilityArea()/2 >= map[0].size()) {
		jMax = map[0].size()-1;
	}
	else {
		jMax = getXCoord() + getVisibilityArea()/2;
	}
	
	if (getYCoord() - getVisibilityArea()/2 < 0) {
		iMin = 0;
	}
	else {
		iMin = getYCoord() - getVisibilityArea()/2;
	}
	if (getYCoord() + getVisibilityArea()/2 >= map.size()) {
		iMax = map.size() - 1;
	}
	else {
		iMax = getYCoord() + getVisibilityArea()/2;
	}

	int sum = 0;
	this->enemies.clear();
	for (int i = iMin; i <= iMax; i++) {
		for (int j = jMin; j <= jMax; j++) {
			if (map[i][j].isOccupied() && ( i!= this->getYCoord() || j!= this->getXCoord() ) ) {
				this->enemies.push_back(map[i][j].getAgentId());
			}
		}
	}
	if (this->enemies.size() == 0) {
		this->move(harta);
	}
	else {
		this->attack(Agents);
	}
}

int Agent::getYCoord() {
	return yCoord;
}

int Agent::getId() {
	return id;
}

void Agent::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
	SDL_RenderCopy(renderer, visibilityTexture, &srcRectVisibility, &destRectVisibility);
	this->armor->Render();
	this->weapon->Render();
}

void Agent::move(Map &harta) {
	vector<vector<Bloc> > map = harta.getBlocuri();
	harta.getBlocuri()[this->yCoord][this->xCoord].setIsOccupied(false);
	harta.getBlocuri()[this->yCoord][this->xCoord].setAgentId(NULL);
	if (this->yCoord > map.size() / 2) {
		this->yCoord -= this->visibilityArea / 2;
	}
	else {
		this->yCoord += this->visibilityArea / 2;
	}
	if (this->xCoord > map[0].size() / 2) {
		this->xCoord -= this->visibilityArea / 2;
	}
	else {
		this->xCoord += this->visibilityArea / 2;
	}
	harta.getBlocuri()[this->yCoord][this->xCoord].setIsOccupied(true);
	harta.getBlocuri()[this->yCoord][this->xCoord].setAgentId(this->getId());
}

void Agent::attack(vector<Agent*> Agents) {
	vector<Agent*> inamici;
	for (int enemyId : this->enemies) {
		for (Agent* agent : Agents) {
			if (agent->getId() == enemyId) {
				inamici.push_back(agent);
			}
		}
	}
	if (inamici.size() > 0)
	{
		Agent* minHp = inamici[0];
		for (Agent* agent : inamici) {
			if (agent->getHp() < minHp->getHp()) {
				minHp = agent;
			}
		}
		cout << endl <<" agentul: "<< this->getId() << " l-a atacat pe agentul: " << minHp->getId()<<" care are "<<minHp->armor->getName()<<" cu "<<this->weapon->getName();
		minHp->takeDamage((minHp->armor->calculateTotalDamage(*this->weapon))*(1-(this->armor->getWeight())), Agents);
	}
}

void Agent::takeDamage(int value, vector<Agent*>Agents) {
	cout << " si i-a dat " << value << " damage"<<endl;
	if (this->armor->getName() == "CeramicArmor") {
		this->armor->setHp( int(this->armor->getHp() * 0.4f) );
	}
	else {
		this->armor->setHp(int(this->armor->getHp() * 0.9f));
	}
	this->hp -= value;
	int index = 0;
}

int Agent::getHp() {
	return this->hp;
}

vector<int> Agent::getEnemies() {
	return this->enemies;
}

void Agent::Update() {
	
	if (xpos < this->getXCoord()*32) {
		xpos++;
	}
	else if(xpos > this->getXCoord()*32){
		xpos--;
	}
	
	if (ypos < this->getYCoord()*32) {
		ypos++;
	}
	else if(ypos > this->getYCoord()*32) {
		ypos--;
	}
	
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	srcRectVisibility.h = 32;
	srcRectVisibility.w = 32;
	srcRectVisibility.x = 0;
	srcRectVisibility.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	destRectVisibility.x = xpos - int(float(visibilityArea)/2 * 32 ) +16 ;
	destRectVisibility.y = ypos - int(float(visibilityArea)/2 *32 ) +16;
	destRectVisibility.w =visibilityArea* srcRectVisibility.w;
	destRectVisibility.h =visibilityArea* srcRectVisibility.h;

	this->armor->Update(xpos, ypos);
	this->weapon->Update(xpos, ypos);

}
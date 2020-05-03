#include "Agent.h"

Agent::Agent(const char* texturesheet,const char* visibTexture, SDL_Renderer* ren, int x, int y) :GameObject( texturesheet, ren, x, y) {
	visibilityTexture = TextureManager::LoadTexture(visibTexture, ren);		//se apeleaza constructorul lui GameObject cu lista de initializare si se incarca textura cu ajutorul lui Texture Manager
	this->hp = 100;															//initializam hp-ul agentului
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

void Agent::takeAction(Map &harta,vector<Agent*>Agents) {		// in aceasta metoda agentul va lua o decizie
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
	}																	//aflam aria de vizibilitate a agentului cu iMin, iMax, jMin, jMax

	int sum = 0;
	this->enemies.clear();												//golim lista de inamici pentru a afla noii inamici
	for (int i = iMin; i <= iMax; i++) {
		for (int j = jMin; j <= jMax; j++) {
			if (map[i][j].isOccupied() && ( i!= this->getYCoord() || j!= this->getXCoord() ) ) { // parcurgem aria de vizibilitate iar daca un bloc este marcat ca fiind ocupat si nu este chiar de el
				this->enemies.push_back(map[i][j].getAgentId());		// atunci introducem id-ul inamicului in lista de inamici
			}
		}
	}	
	if (this->enemies.size() == 0) {									// daca lista de inamici este goala
		this->move(harta);												// agentul se v-a muta pe harta
	}
	else {
		this->attack(Agents);											// altfel va ataca (metoda care primeste lista de inamici)
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
	harta.getBlocuri()[this->yCoord][this->xCoord].setIsOccupied(false);		//setam blocul de pe care pleaca agentul ca fiind neocupat
	harta.getBlocuri()[this->yCoord][this->xCoord].setAgentId(NULL);
	if (this->yCoord > map.size() / 2) {
		this->yCoord -= this->visibilityArea / 2;
	}
	else {
		this->yCoord += this->visibilityArea / 2;
	}
	if (this->xCoord > map[0].size() / 2) {										//calculam noua locatie
		this->xCoord -= this->visibilityArea / 2;
	}
	else {
		this->xCoord += this->visibilityArea / 2;
	}
	harta.getBlocuri()[this->yCoord][this->xCoord].setIsOccupied(true);			//setam blocul din noua locatie ca fiind ocupat
	harta.getBlocuri()[this->yCoord][this->xCoord].setAgentId(this->getId());
}

void Agent::attack(vector<Agent*> Agents) {
	vector<Agent*> inamici;
	for (int enemyId : this->enemies) {											//cautam agentii cu id-ul inamicilor si il introducem intr-un vector
		for (Agent* agent : Agents) {
			if (agent->getId() == enemyId) {
				inamici.push_back(agent);
			}
		}
	}
	if (inamici.size() > 0)														
	{
		Agent* minHp = inamici[0];											//cautam agentul cu cel mai putin hp
		for (Agent* agent : inamici) {
			if (agent->getHp() < minHp->getHp()) {
				minHp = agent;
			}
		}
		cout << endl <<" agentul: "<< this->getId() << " l-a atacat pe agentul: " << minHp->getId()<<" care are "<<minHp->armor->getName()<<" cu "<<this->weapon->getName();
		minHp->takeDamage((minHp->armor->calculateTotalDamage(*this->weapon))*(1-(this->armor->getWeight())), Agents);
		//punem agentul cu hp minim sa isi ia damage care este calculat in functie de armura sa, arma oponentului si armura oponentului;
	}
}

void Agent::takeDamage(int value, vector<Agent*>Agents) {
	cout << " si i-a dat " << value << " damage"<<endl;
	if (this->armor->getName() == "CeramicArmor") {
		this->armor->setHp( int(this->armor->getHp() * 0.4f) );	//armura isi pierde din hp in functie de tipul ei
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
	
	if (xpos < this->getXCoord()*32) {					//schimbam positia pe partea de grafica (positia mostenita din gameObject)
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
	destRect.w = srcRect.w;													//setam dimensiunile texturii agentului
	destRect.h = srcRect.h;

	destRectVisibility.x = xpos - int(float(visibilityArea)/2 * 32 ) +16 ;
	destRectVisibility.y = ypos - int(float(visibilityArea)/2 *32 ) +16;
	destRectVisibility.w =visibilityArea* srcRectVisibility.w;					//setam dimensiunile texturii agriei de vizibilitate
	destRectVisibility.h =visibilityArea* srcRectVisibility.h;

	this->armor->Update(xpos, ypos);
	this->weapon->Update(xpos, ypos);

}
#include "Game.h"

Agent* player;
Agent* playerAr;
Map* Game::map;
int runda = 0;
int rundaCurenta = 0;
bool finalRound = false;
ObjectManager Game::objects;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, int noAgents, int visibilityArea, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}else {
		isRunning = false;
	}

	map = new Map(renderer, width / 32, height / 32);
	cout << *map;
	cout << "press any button to start the game" << endl;

	srand(time(NULL));
	for (int i = 0; i < noAgents;i++) {
		int posX = 0, posY = 0;
		do {
			 posX = (rand() % (width / 32)) * 32;
			 posY = (rand() % (height / 32)) * 32;
		} while (map->getBlocuri()[posX / 32][posY / 32].isOccupied());
		int armorType = rand() % 3;

		Armor* armura = new KevlarArmor("assets/kevlarArmor.png", renderer, posX, posY);
		switch (armorType) {
		case 0:
			armura = new KevlarArmor("assets/kevlarArmor.png", renderer, posX, posY);
			break;
		case 1:
			armura = new CeramicArmor("assets/ceramicArmor.png", renderer, posX, posY);
			break;
		case 2:
			armura = new JuggernautArmor("assets/juggernaut.png", renderer, posX, posY);
			break;
		}
		int weaponType = rand() % 3;
		Weapon* arma = new M4a1s("assets/m4a1s.png", renderer, posX, posY);
		switch (weaponType) {
		case 0:
			arma = new M4a1s("assets/m4a1s.png", renderer, posX, posY);
			break;
		case 1:
			arma = new Sword("assets/sword.png", renderer, posX, posY);
			break;
		case 2:
			arma = new Bazooka("assets/bazooka.png", renderer, posX, posY);
			break;
		}

		Game::objects.pushAgent(new Agent("assets/agent.png", "assets/visibility.png", renderer, posX, posY));
		Game::objects.getAgents()[i]->setId(i+1);
		Game::objects.getAgents()[i]->setArmor(armura);
		Game::objects.getAgents()[i]->setWeapon(arma);
		Game::objects.getAgents()[i]->setVisibilityArea(visibilityArea);
		Game::objects.getAgents()[i]->setXCoord(posX / 32);
		Game::objects.getAgents()[i]->setYCoord(posY / 32);
		map->getBlocuri()[posY / 32][posX / 32].setIsOccupied(true);
		map->getBlocuri()[posY / 32][posX / 32].setAgentId(Game::objects.getAgents()[i]->getId());
	}
	
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			runda++;
			cout << endl << "------------------------------"<<endl;
			cout << "round "<<runda<<endl;
			break;
		default:
			break;
	}
}

void Game::update() {

	if (runda > rundaCurenta) {

		for (Agent* agent : Game::objects.getAgents()) {
			agent->takeAction(*map,objects.getAgents());

			if (agent->getHp() <= 0) {
				int index = 0;
				for (int i = 0; i < objects.getAgents().size(); i++) {
					if (agent->getId() == objects.getAgents()[i]->getId()) {
						index = i;
						break;
					}
				}
				vector<Agent*> nou;
				for (int i = 0; i < objects.getAgents().size(); i++) {
					if (i != index) {
						nou.push_back(objects.getAgents()[i]);
					}
				}
				objects.setAgents(nou);
				map->getBlocuri()[agent->getYCoord()][agent->getXCoord()].setIsOccupied(false);
				map->getBlocuri()[agent->getYCoord()][agent->getXCoord()].setAgentId(NULL);
			}
		}
		
		cout << "player ids on map:";
		cout << endl;
		cout << *map;
		
		rundaCurenta++;

		if (map->haveWinner()) {
			if (finalRound == true) {
				isRunning = false;
			}
			else {
				finalRound = true;
			}
		}
	}
	for (Agent* agent : Game::objects.getAgents()) {
		agent->Update();
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap(renderer);
	for (Agent* agent : Game::objects.getAgents()) {
		agent->Render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

Map* Game::getMap() {
	return Game::map;
}


bool Game::running() {
	return isRunning;
}
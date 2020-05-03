#include"SDL.h"
#include"Game.h"

Game* game = nullptr;

int main(int args, char *argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	//
	int noBlocksX;
	int noBlocksY;
	int noAgents;
	int visibilityArea;
	cout << "how big is the map?"<<endl;
	cin >> noBlocksY >> noBlocksX;
	cout << "how many agents?" << endl;
	cin >> noAgents;
	cout << "agents visibility area: " << endl;
	cin >> visibilityArea;
	//

	game = new Game();
	game->init("tema",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,32*noBlocksX,32*noBlocksY,noAgents,visibilityArea,false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();


	return 0;
}
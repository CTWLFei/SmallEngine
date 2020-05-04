#include "se_game/GameEngine.h"

int GameEngine::TARGET_FPS = 75;
int GameEngine::TARGET_UPS = 30;

GameEngine::GameEngine(string windowTitle, int width, int height, bool vSync, GameLogic* gameLogic)
{
	window = new Window(windowTitle, width, height, vSync);
	window->active();
	mouseInput = new MouseInput();
	mouseInput->active();
	this->gameLogic = gameLogic;
	timer = new Timer();
}
GameEngine::~GameEngine()
{
	delete window;
	delete timer;
}
void GameEngine::run()
{
	try {
		init();
		gameLoop();
	}
	catch (exception e) {
		cout << e.what();
	}
	
}
void GameEngine::init()
{
	window->init();
	timer->init();
	mouseInput->init(window);
	gameLogic->init(window);
}
void GameEngine::gameLoop()
{
	float elapsedTime;
	float accumulator = 0.0;
	float interval = 1.0 / TARGET_UPS;
	bool running = true;

	while (running && !window->windowShouldClose()) {
		elapsedTime = timer->getElapsedTime();
		accumulator += elapsedTime;
		input();

		while (accumulator >= interval) {
			update(interval);
			accumulator -= interval;
		}

		render();

		if (!window->isvSync())
			sync();
	}
}
void GameEngine::sync()
{
	float loopSlot = 1.0 / TARGET_FPS;
	double endTime = timer->getLastLoopTime() + loopSlot;
	while (timer->getTime() < endTime) {
		try {
			this_thread::sleep_for(1s);
		}
		catch (exception e) {

		}
	}
	
}
void GameEngine::input()
{
	mouseInput->input(window);
	gameLogic->input(window, mouseInput);
}
void GameEngine::update(float interval)
{
	gameLogic->update(interval, mouseInput);
}
void GameEngine::render()
{
	gameLogic->render(window);
	window->update();
}

void GameEngine::cleanup()
{
	gameLogic->cleanup();
}
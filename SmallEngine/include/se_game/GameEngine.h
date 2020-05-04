#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include <thread>
#include <se_aux/Timer.h>
#include <se_aux/Window.h>
#include "GameLogic.h"
#include <se_core/MouseInput.h>
class GameEngine {
public:
	static int TARGET_FPS;
	static int TARGET_UPS;

	GameEngine(string windowTitle, int width, int height, bool vSync, GameLogic* gameLogic);
	~GameEngine();

	void run();
private:
	void init();
	void gameLoop();
	void sync();
	void input();
	void update(float interval);
	void render();
	void cleanup();
private:
	Window* window;
	Timer* timer;
	GameLogic* gameLogic;
	MouseInput* mouseInput;
};

#endif
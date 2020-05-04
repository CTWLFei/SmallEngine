#include <iostream>
#include <GLAD/glad.h>
#include <glfw/glfw3.h>
#include <se_game/GameEngine.h>
#include <se_game/GameLogicDummy.h>
using namespace std;

int main(int argc, char** argv) {
	try {
		bool vSync = true;
		GameLogic* dummyGame = new GameLogicDummy();
		GameEngine* gameEngine = new GameEngine("SmallEngine", 1024, 576, vSync, dummyGame);
		thread t1(&GameEngine::run, gameEngine);
		t1.join();
	}
	catch (exception e) {
		cout << e.what();
	}
	return -1;
}
#include <iostream>
#include <GLAD/glad.h>
#include <glfw/glfw3.h>
#include <se_game/GameEngine.h>
#include <se_game/GameLogicDummy.h>
#include <se_aux/Utils.h>
#include <string>

using namespace std;



int main(int argc, char** argv) {
	try {
		bool vSync = true;
		Utils::ExtractPath(*argv);
		GameLogic* dummyGame = new GameLogicDummy();
		GameEngine* gameEngine = new GameEngine("SmallEngine", 800, 600, vSync, dummyGame);
		thread t1(&GameEngine::run, gameEngine);
		t1.join();
	}
	catch (exception e) {
		cout << e.what();
	}
	return -1;
}
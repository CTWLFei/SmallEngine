#ifndef __GAMELOGICDUMMY_H__
#define __GAMELOGICDUMMY_H__

#include "GameLogic.h"
#include <se_core/Renderer.h>
#include <se_core/MouseInput.h>

class GameLogicDummy : public GameLogic {
public:
	GameLogicDummy();
	~GameLogicDummy();
	virtual void init(Window* window);
	virtual void input(Window* window, MouseInput* mouseInput);
	virtual void update(float interval, MouseInput* mouseInput);
	virtual void render(Window* window);
	virtual void cleanup();
private:
	static float MOUSE_SENSITIVITY;
	static float CAMERA_POS_STEP;

	vec3 cameraInc;
	Renderer* renderer;
	Camera* camera;
	vector<GameItem*> gameItems;

	
};

#endif
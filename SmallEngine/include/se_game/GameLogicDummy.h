#ifndef __GAMELOGICDUMMY_H__
#define __GAMELOGICDUMMY_H__

#include "GameLogic.h"
#include <se_core/Renderer.h>
#include <se_core/MouseInput.h>
#include <se_game/Scene.h>
#include <se_game/se_game_item/Terrain.h>

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

	void setupLights();

	vec3 cameraInc;
	Renderer* renderer;
	Camera* camera;
	vector<GameItem*> gameItems;
	vec3 ambientLight;
	DirectionalLight* directionalLight;
	vector<PointLight*> pointLight;
	vector<SpotLight*> spotLight;
	Scene* scene;
	Terrain* terrain;
	float lightAngle;

	int pressedKeyCode;
};

#endif
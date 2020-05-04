#include <se_game/GameLogicDummy.h>


float GameLogicDummy::MOUSE_SENSITIVITY = 0.2f;
float GameLogicDummy::CAMERA_POS_STEP = 0.05f;
GameLogicDummy::GameLogicDummy()
{
	renderer = new Renderer();
	camera = new Camera();
}
GameLogicDummy::~GameLogicDummy()
{
	delete renderer;
}
void GameLogicDummy::init(Window* window)
{
	renderer->init(window);
	// Create the Mesh
	float positions[] = {
		// V0
		-0.5f, 0.5f, 0.5f,
			// V1
			-0.5f, -0.5f, 0.5f,
			// V2
			0.5f, -0.5f, 0.5f,
			// V3
			0.5f, 0.5f, 0.5f,
			// V4
			-0.5f, 0.5f, -0.5f,
			// V5
			0.5f, 0.5f, -0.5f,
			// V6
			-0.5f, -0.5f, -0.5f,
			// V7
			0.5f, -0.5f, -0.5f,
			// For text coords in top face
			// V8: V4 repeated
			-0.5f, 0.5f, -0.5f,
			// V9: V5 repeated
			0.5f, 0.5f, -0.5f,
			// V10: V0 repeated
			-0.5f, 0.5f, 0.5f,
			// V11: V3 repeated
			0.5f, 0.5f, 0.5f,
			// For text coords in right face
			// V12: V3 repeated
			0.5f, 0.5f, 0.5f,
			// V13: V2 repeated
			0.5f, -0.5f, 0.5f,
			// For text coords in left face
			// V14: V0 repeated
			-0.5f, 0.5f, 0.5f,
			// V15: V1 repeated
			-0.5f, -0.5f, 0.5f,
			// For text coords in bottom face
			// V16: V6 repeated
			-0.5f, -0.5f, -0.5f,
			// V17: V7 repeated
			0.5f, -0.5f, -0.5f,
			// V18: V1 repeated
			-0.5f, -0.5f, 0.5f,
			// V19: V2 repeated
			0.5f, -0.5f, 0.5f, };
	float textCoords[] = {
		0.0f, 0.0f,
			0.0f, 0.5f,
			0.5f, 0.5f,
			0.5f, 0.0f,
			0.0f, 0.0f,
			0.5f, 0.0f,
			0.0f, 0.5f,
			0.5f, 0.5f,
			// For text coords in top face
			0.0f, 0.5f,
			0.5f, 0.5f,
			0.0f, 1.0f,
			0.5f, 1.0f,
			// For text coords in right face
			0.0f, 0.0f,
			0.0f, 0.5f,
			// For text coords in left face
			0.5f, 0.0f,
			0.5f, 0.5f,
			// For text coords in bottom face
			0.5f, 0.0f,
			1.0f, 0.0f,
			0.5f, 0.5f,
			1.0f, 0.5f, };
	int indices[] = {
		// Front face
		0, 1, 3, 3, 1, 2,
			// Top Face
			8, 10, 11, 9, 8, 11,
			// Right face
			12, 13, 7, 5, 12, 7,
			// Left face
			14, 15, 6, 4, 14, 6,
			// Bottom face
			16, 18, 19, 17, 16, 19,
			// Back face
			4, 6, 7, 5, 4, 7, };
	Texture* texture = new Texture("D:\\VS2015Project\\SmallEngine\\SmallEngine\\texture\\grassblock.png");
	Mesh* mesh = new Mesh(positions, 20, textCoords, 20, indices, 36, texture);
	GameItem* gameItem1 = new GameItem(mesh);
	gameItem1->setScale(0.5f);
	gameItem1->setPosition(0, 0, -2);
	GameItem* gameItem2 = new GameItem(mesh);
	gameItem2->setScale(0.5f);
	gameItem2->setPosition(0.5f, 0.5f, -2);
	GameItem* gameItem3 = new GameItem(mesh);
	gameItem3->setScale(0.5f);
	gameItem3->setPosition(0, 0, -2.5f);
	GameItem* gameItem4 = new GameItem(mesh);
	gameItem4->setScale(0.5f);
	gameItem4->setPosition(0.5f, 0, -2.5f);
	
	gameItems.push_back(gameItem1);
	gameItems.push_back(gameItem2);
	gameItems.push_back(gameItem3);
	gameItems.push_back(gameItem4);
}

void GameLogicDummy::input(Window* window, MouseInput* mouseInput)
{
	cameraInc = vec3(0, 0, 0);
	if (window->isKeyPressed(GLFW_KEY_W)) {
		cameraInc[2] = -1;
	}
	else if (window->isKeyPressed(GLFW_KEY_S)) {
		cameraInc[2] = 1;
	}
	if (window->isKeyPressed(GLFW_KEY_A)) {
		cameraInc[0] = -1;
	}
	else if (window->isKeyPressed(GLFW_KEY_D)) {
		cameraInc[0] = 1;
	}
	if (window->isKeyPressed(GLFW_KEY_Z)) {
		cameraInc[1] = -1;
	}
	else if (window->isKeyPressed(GLFW_KEY_X)) {
		cameraInc[1] = 1;
	}
}

void GameLogicDummy::update(float interval, MouseInput* mouseInput)
{
	// Update camera position
	camera->movePosition(cameraInc[0] * CAMERA_POS_STEP, cameraInc[1] * CAMERA_POS_STEP, cameraInc[2] * CAMERA_POS_STEP);

	// Update camera based on mouse            
	if (mouseInput->isRightButtonPressed()) {
		vec2 rotVec = mouseInput->getDisplVec();
		camera->moveRotation(rotVec[0] * MOUSE_SENSITIVITY, rotVec[1] * MOUSE_SENSITIVITY, 0);
	}
}

void GameLogicDummy::render(Window* window)
{
	renderer->render(window, camera, gameItems);
}

void GameLogicDummy::cleanup()
{
	renderer->cleanup();
	for (GameItem* gameItem : gameItems) {
		gameItem->getMesh()->cleanup();
	}
}
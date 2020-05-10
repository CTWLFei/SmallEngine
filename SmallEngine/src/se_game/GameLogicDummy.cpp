#include <se_game/GameLogicDummy.h>
#include <se_core/se_graph/se_loader/OBJLoader.h>

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
	Mesh* mesh = OBJLoader::loadMesh("./models/bunny.obj");
	Texture* texture = new Texture("./textures/grassblock.png");
	mesh->setTexture(texture);
	GameItem* gameItem = new GameItem(mesh);
	gameItem->setScale(0.5f);
	gameItem->setPosition(0, 0, -2);

	gameItems.push_back(gameItem);
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
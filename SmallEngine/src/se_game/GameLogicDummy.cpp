#include <se_game/GameLogicDummy.h>
#include <se_core/se_graph/se_loader/OBJLoader.h>
#include <se_core/se_graph/se_material/Material.h>
#include <se_core/se_graph/se_light/PointLight.h>

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
	float reflectant = 1.0;
	Mesh* mesh = OBJLoader::loadMesh("./models/bunny.obj");
	Texture* texture = new Texture("./textures/grassblock.png");
	Material* material = new Material(texture, reflectant);
	mesh->setMaterial(material);
	GameItem* gameItem = new GameItem(mesh);
	gameItem->setScale(0.5f);
	gameItem->setPosition(0, 0, -2);

	gameItems.push_back(gameItem);

	ambientLight = vec3(0.3f, 0.3f, 0.3f);
	//point light
	vec3 lightColour = vec3(1, 1, 1);
	vec3 lightPosition = vec3(0, 0, 1);
	float lightIntensity = 1.0f;
	pointLight.push_back(new PointLight(lightColour, lightPosition, lightIntensity));
	Attenuation* att = new Attenuation(0.0f, 0.0f, 1.0f);
	pointLight[0]->setAttenuation(att);

	//spot light
	lightPosition = vec3(0, 0, 10.0);
	PointLight* lightSource = new PointLight(lightColour, lightPosition, lightIntensity, att);
	vec3 coneDir = vec3(0, 0, -1);
	float cutoff = cos(3.1415926 / 3.0 * 4.0);
	spotLight.push_back(new SpotLight(lightSource, coneDir, cutoff));

	lightPosition = vec3(-1, 0, 0);
	directionalLight = new DirectionalLight(vec3(1, 1, 1), lightPosition, lightIntensity);
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
	//renderer->render(window, camera, gameItems);
	renderer->render(window, camera, gameItems, ambientLight, pointLight, spotLight, directionalLight);
}

void GameLogicDummy::cleanup()
{
	renderer->cleanup();
	for (GameItem* gameItem : gameItems) {
		gameItem->getMesh()->cleanup();
	}
}
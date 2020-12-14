#include <se_game/GameLogicDummy.h>
#include <se_core/se_graph/se_loader/OBJLoader.h>
#include <se_core/se_graph/se_material/Material.h>
#include <se_core/se_graph/se_light/PointLight.h>
#include <se_game/se_game_item/SkyBox.h>


#include <math.h>

float GameLogicDummy::MOUSE_SENSITIVITY = 0.2f;
float GameLogicDummy::CAMERA_POS_STEP = 0.05f;
GameLogicDummy::GameLogicDummy()
{
	renderer = new Renderer();
	camera = new Camera();
	cameraInc = vec3(0.0f, 0.0f, 0.0f);
	lightAngle = -90;
}
GameLogicDummy::~GameLogicDummy()
{
	delete renderer;
}
void GameLogicDummy::init(Window* window)
{
	renderer->init(window);
	scene = new Scene();
	float reflectant = 1.0;
	Mesh* mesh = OBJLoader::loadMesh("./models/cube.obj");
	Texture* texture = new Texture("./textures/grassblock.png");
	Material* material = new Material(texture, reflectant);
	mesh->setMaterial(material);
	float blockScale = 5.0f;
	float skyBoxScale = 50.0f;
	float extension = 2.0f;

	float startx = extension * (-skyBoxScale + blockScale);
	float startz = extension * (skyBoxScale - blockScale);
	float starty = -1.0f;
	float inc = blockScale * 2;

	float posx = startx;
	float posz = startz;
	float incy = 0.0f;
	int NUM_ROWS = (int)(extension * skyBoxScale * 2 / inc);
	int NUM_COLS = (int)(extension * skyBoxScale * 2 / inc);
	vector<GameItem*> gameItems;
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			GameItem* gameItem = new GameItem(mesh);
			gameItem->setScale(blockScale);
			incy = rand() > 0.9f ? blockScale * 2 : 0;
			gameItem->setPosition(posx, starty + incy, posz);
			gameItems.push_back(gameItem);

			posx += inc;
		}
		posx = startx;
		posz -= inc;
	}
	//scene->setGameItems(gameItems);
	// Setup  SkyBox
	SkyBox* skyBox = new SkyBox("./models/skybox.obj", "./textures/skybox.png");
	skyBox->setScale(skyBoxScale);

	float terrainScale = 10;
	//int terrainSize = 3;
	int terrainSize = 3;
	float minY = -0.1f;
	float maxY = 0.1f;
	int textInc = 40;
	terrain = new Terrain(terrainSize, terrainScale, minY, maxY, "./textures/heightmap.png", "./textures/terrain.png", textInc);
	scene->setGameItems(terrain->GetGameItems());

	scene->setFog(new Fog(true, vec3(0.5f, 0.5f, 0.5f), 0.15f));

	scene->setSkyBox(skyBox);

	setupLights();

	//ambientLight = vec3(0.3f, 0.3f, 0.3f);
	////point light
	//vec3 lightColour = vec3(1, 1, 1);
	//vec3 lightPosition = vec3(0, 0, 1);
	//float lightIntensity = 1.0f;
	//pointLight.push_back(new PointLight(lightColour, lightPosition, lightIntensity));
	//Attenuation* att = new Attenuation(0.0f, 0.0f, 1.0f);
	//pointLight[0]->setAttenuation(att);

	////spot light
	//lightPosition = vec3(0, 0, 10.0);
	//PointLight* lightSource = new PointLight(lightColour, lightPosition, lightIntensity, att);
	//vec3 coneDir = vec3(0, 0, -1);
	//float cutoff = cos(3.1415926 / 3.0 * 4.0);
	//spotLight.push_back(new SpotLight(lightSource, coneDir, cutoff));

	//lightPosition = vec3(-1, 0, 0);
	//directionalLight = new DirectionalLight(vec3(1, 1, 1), lightPosition, lightIntensity);

	camera->setPosition(0, 5, 0);
	camera->setRotation(0, 90, 0);
}

void GameLogicDummy::input(Window* window, MouseInput* mouseInput)
{
	cameraInc = vec3(0, 0, 0);
	if (window->isKeyPressed(GLFW_KEY_W)) {
		pressedKeyCode = GLFW_KEY_W;
		cameraInc[2] = -1;
	}
	else if (window->isKeyPressed(GLFW_KEY_S)) {
		pressedKeyCode = GLFW_KEY_S;
		cameraInc[2] = 1;
	}
	if (window->isKeyPressed(GLFW_KEY_A)) {
		pressedKeyCode = GLFW_KEY_A;
		cameraInc[0] = -1;
	}
	else if (window->isKeyPressed(GLFW_KEY_D)) {
		pressedKeyCode = GLFW_KEY_D;
		cameraInc[0] = 1;
	}
	if (window->isKeyPressed(GLFW_KEY_Z)) {
		pressedKeyCode = GLFW_KEY_Z;
		cameraInc[1] = -1;
	}
	else if (window->isKeyPressed(GLFW_KEY_X)) {
		pressedKeyCode = GLFW_KEY_X;
		cameraInc[1] = 1;
	}

	if (window->isKeyReleased(GLFW_KEY_W) && pressedKeyCode == GLFW_KEY_W) {
		pressedKeyCode = -1;
		cameraInc[2] = 0;
	}
	else if (window->isKeyReleased(GLFW_KEY_S) && pressedKeyCode == GLFW_KEY_S) {
		pressedKeyCode = -1;
		cameraInc[2] = 0;
	}
	if (window->isKeyReleased(GLFW_KEY_A) && pressedKeyCode == GLFW_KEY_A) {
		pressedKeyCode = -1;
		cameraInc[0] = 0;
	}
	else if (window->isKeyReleased(GLFW_KEY_D) && pressedKeyCode == GLFW_KEY_D) {
		pressedKeyCode = -1;
		cameraInc[0] = 0;
	}
	if (window->isKeyReleased(GLFW_KEY_Z) && pressedKeyCode == GLFW_KEY_Z) {
		pressedKeyCode = -1;
		cameraInc[1] = 0;
	}
	else if (window->isKeyReleased(GLFW_KEY_X) && pressedKeyCode == GLFW_KEY_X) {
		pressedKeyCode = -1;
		cameraInc[1] = 0;
	}
}

void GameLogicDummy::update(float interval, MouseInput* mouseInput)
{
	// Update camera position
	/*camera->movePosition(cameraInc[0] * CAMERA_POS_STEP, cameraInc[1] * CAMERA_POS_STEP, cameraInc[2] * CAMERA_POS_STEP);*/

	// Update camera based on mouse            
	if (mouseInput->isRightButtonPressed()) {
		vec2 rotVec = mouseInput->getDisplVec();
		camera->moveRotation(rotVec[0] * MOUSE_SENSITIVITY, rotVec[1] * MOUSE_SENSITIVITY, 0);
	}

	// Update camera position
	if(cameraInc[0] != 0 || cameraInc[1] != 0 || cameraInc[2] != 0)
		camera->movePosition(cameraInc[0] * CAMERA_POS_STEP, cameraInc[1] * CAMERA_POS_STEP, cameraInc[2] * CAMERA_POS_STEP);

	SceneLight* sceneLight = scene->getSceneLight();

	// Update directional light direction, intensity and colour
	DirectionalLight* directionalLight = sceneLight->getDirectionalLight();
	lightAngle += 1.1f;
	if (lightAngle > 90) {
		directionalLight->setIntensity(0);
		if (lightAngle >= 360) {
			lightAngle = -90;
		}
		sceneLight->setAmbientLight(0.3, 0.3, 0.4);
	}
	else if (lightAngle <= -80 || lightAngle >= 80) {
		float factor = 1 - (float)(abs(lightAngle) - 80) / 10.0f;
		sceneLight->setAmbientLight(factor, factor, factor);
		directionalLight->setIntensity(factor);
		directionalLight->setColor(vec3(directionalLight->getColor()[0], max(factor, 0.9f), max(factor, 0.5f)));
	}
	else {
		sceneLight->setAmbientLight(1, 1, 1);
		directionalLight->setIntensity(1);
		directionalLight->setColor(vec3(1, 1, 1));
	}
	double angRad = (lightAngle / 180) * PI;
	directionalLight->setDirection(vec3(sin(angRad), cos(angRad), directionalLight->getDirection()[2]));
}

void GameLogicDummy::render(Window* window)
{
	//renderer->render(window, camera, gameItems);
	renderer->render(window, camera, scene);
}

void GameLogicDummy::cleanup()
{
	renderer->cleanup();
	scene->cleanup();
}

void GameLogicDummy::setupLights()
{
	SceneLight* sceneLight = new SceneLight();
	scene->setSceneLight(sceneLight);

	// Ambient Light
	vec3 ambientLight = vec3(1.0f, 1.0f, 1.0f);
	sceneLight->setAmbientLight(ambientLight);

	// Directional Light
	float lightIntensity = 1.0f;
	vec3 lightPosition = vec3(-1, 0, 0);
	sceneLight->setDirectionalLight(new DirectionalLight(vec3(1, 1, 1), lightPosition, lightIntensity));
}
#include <se_core/Renderer.h>

float Renderer::fov = 90.0;
float Renderer::zNear = 0.01;
float Renderer::zFar = 1000.0;
Renderer::Renderer()
{
	transformation = new Transform();
	specularPower = 10.0;
}
Renderer::~Renderer()
{

}
void Renderer::init(Window* window)
{
	// Create shader
	shaderProgram = new ShaderProgram("D:\\VS2015Project\\SmallEngine\\SmallEngine\\shader\\test.vs", "D:\\VS2015Project\\SmallEngine\\SmallEngine\\shader\\test.fs");

	// Create uniforms for modelView and projection matrices and texture
	shaderProgram->createUniform("projectionMatrix");
	shaderProgram->createUniform("modelViewMatrix");
	shaderProgram->createUniform("texture_sampler");
	// Create uniform for material
	shaderProgram->createMaterialUniform("material");
	// Create lighting related uniforms
	shaderProgram->createUniform("specularPower");
	shaderProgram->createUniform("ambientLight");
	shaderProgram->createPointLightUniform("pointLight");
}
void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::render(Window* window, Camera* camera, vector<GameItem*>& gameItems)
{
	clear();

	if (window->isResized()) {
		glViewport(0, 0, window->getWidth(), window->getHeight());
		window->setResized(false);
	}

	shaderProgram->bind();

	// Update projection Matrix
	mat4 projectionMatrix = transformation->getProjectionMatrix(fov, window->getWidth(), window->getHeight(), zNear, zFar);
	shaderProgram->setMat4Uniform("projectionMatrix", projectionMatrix, 1);

	// Update view Matrix
	mat4 viewMatrix = transformation->getViewMatrix(*camera);

	shaderProgram->setTextureUniform(gameItems[0]->getMesh()->getMaterial()->getTexture()->id(), "texture_sampler", GL_TEXTURE_2D);
	// Render each gameItem
	for (GameItem* gameItem : gameItems) {
		// Set model view matrix for this item
		mat4 modelViewMatrix = transformation->getModelViewMatrix(*gameItem, viewMatrix);
		vec4 test_vec1 = vec4(0.5, 0.5, 0.5, 1.0);
		vec4 test_vec2 = vec4(-0.5, -0.5, -0.5, 1.0);
		vec4 test_result1 = test_vec1 * modelViewMatrix;
		vec4 test_result2 = test_vec2 * modelViewMatrix;
		shaderProgram->setMat4Uniform("modelViewMatrix", modelViewMatrix, 1);
		// Render the mes for this game item
		gameItem->getMesh()->render();
	}

	shaderProgram->unbind();
}

void Renderer::render(Window* window, Camera* camera, vector<GameItem*>& gameItems, vec3 ambientLight, PointLight* pointLight)
{
	clear();

	if (window->isResized()) {
		glViewport(0, 0, window->getWidth(), window->getHeight());
		window->setResized(false);
	}

	shaderProgram->bind();

	mat4 projectionMatrix = transformation->getProjectionMatrix(fov, window->getWidth(), window->getHeight(), zNear, zFar);
	shaderProgram->setMat4Uniform("projectionMatrix", projectionMatrix, 1);

	// Update view Matrix
	mat4 viewMatrix = transformation->getViewMatrix(*camera);

	// Update Light Uniforms
	shaderProgram->setFloatUniform("ambientLight", &(ambientLight[0]), 3, 1);
	shaderProgram->setFloatUniform("specularPower", &specularPower, 1, 1);

	PointLight* curPointLight = new PointLight(*pointLight);
	vec3 lightPos = curPointLight->getPosition();
	vec4 aux = vec4(lightPos, 1.0);
	aux = aux * viewMatrix;
	lightPos[0] = aux[0];
	lightPos[1] = aux[1];
	lightPos[2] = aux[2];
	shaderProgram->setPointLightUniform("pointLight", curPointLight);
	shaderProgram->setTextureUniform(0, "texture_sampler", GL_TEXTURE_2D);

	// Render each gameItem
	for (GameItem* gameItem : gameItems) {
		Mesh* mesh = gameItem->getMesh();
		// Set model view matrix for this item
		mat4 modelViewMatrix = transformation->getModelViewMatrix(*gameItem, viewMatrix);
		shaderProgram->setMat4Uniform("modelViewMatrix", modelViewMatrix, 1);
		// Render the mes for this game item
		shaderProgram->setMaterialUniform("material", mesh->getMaterial());
		mesh->render();
	}
}

void Renderer::cleanup()
{
	if (shaderProgram != NULL) {
		shaderProgram->cleanup();
	}
}
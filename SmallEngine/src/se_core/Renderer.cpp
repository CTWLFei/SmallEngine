#include <se_core/Renderer.h>

float Renderer::fov = 90.0;
float Renderer::zNear = 0.01;
float Renderer::zFar = 1000.0;
Renderer::Renderer()
{
	transformation = new Transform();
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

	shaderProgram->setTextureUniform(gameItems[0]->getMesh()->getTextureId(), "texture_sampler", GL_TEXTURE_2D);
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
void Renderer::cleanup()
{
	if (shaderProgram != NULL) {
		shaderProgram->cleanup();
	}
}
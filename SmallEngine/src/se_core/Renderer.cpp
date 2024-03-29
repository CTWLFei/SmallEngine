#include <se_core/Renderer.h>
#include <se_aux/Utils.h>

float Renderer::fov = 50.0;
float Renderer::zNear = 1.0;
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
	setupSceneShader();
	setupSkyBoxShader();
	setupDepthShader();
}
void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Window* window, Camera* camera, Scene* scene)
{
	clear();

	renderDepthMap(window, camera, scene);

	if (window->isResized()) {
		glViewport(0, 0, window->getWidth(), window->getHeight());
		window->setResized(false);
	}

	// Update projection and view atrices once per render cycle
	transformation->updateProjectionMatrix(fov, window->getWidth(), window->getHeight(), zNear, zFar);
	transformation->updateViewMatrix(*camera);

	renderScene(window, camera, scene);

	renderSkyBox(window, camera, scene);

}

void Renderer::cleanup()
{
	if (sceneShaderProgram != NULL) {
		sceneShaderProgram->cleanup();
	}
}

void Renderer::renderLights(const mat4& viewMatrix, SceneLight* sceneLight)
{
	vec3 ambientLight = sceneLight->getAmbientLight();
	vector<PointLight*> pointLights = sceneLight->getPointLightList();
	vector<SpotLight*> spotLights = sceneLight->getSpotLightList();
	DirectionalLight* dirLight = sceneLight->getDirectionalLight();

	// Update Light Uniforms
	sceneShaderProgram->setFloatUniform("ambientLight", &(ambientLight[0]), 3, 1);
	sceneShaderProgram->setFloatUniform("specularPower", &specularPower, 1, 1);
	//point light
	for (int i = 0; i < pointLights.size(); i++)
	{
		PointLight* pointLight = new PointLight(*pointLights[i]);
		vec4 pointLightPos(pointLight->getPosition(), 1.0);
		vec4 pointLightPosInView = pointLightPos * viewMatrix;
		vec3 newPointLightPos(pointLightPosInView[0], pointLightPosInView[1], pointLightPosInView[2]);
		pointLight->setPosition(newPointLightPos);
		sceneShaderProgram->setPointLightUniform("pointLights", pointLight, i);
	}

	//spot light
	for (int i = 0; i < spotLights.size(); i++)
	{
		SpotLight* spotLight = new SpotLight(*spotLights[i]);
		vec4 lightPos(spotLight->getPointLight()->getPosition(), 1.0);
		vec4 lightPosInView = lightPos * viewMatrix;
		vec3 newLightPos(lightPosInView[0], lightPosInView[1], lightPosInView[2]);
		spotLight->getPointLight()->setPosition(newLightPos);
		sceneShaderProgram->setSpotLightUniform("spotLights", spotLight, i);
	}

	DirectionalLight* dirLightCopy = new DirectionalLight(*dirLight);
	vec4 lightDir(dirLightCopy->getDirection(), 0);
	vec4 lightDirInView = lightDir * viewMatrix;
	vec3 newLightDir = vec3(lightDirInView[0], lightDirInView[1], lightDirInView[2]);
	dirLightCopy->setDirection(newLightDir);
	sceneShaderProgram->setDirectionalLightUniform("directionalLight", dirLightCopy);
}

void Renderer::renderScene(Window* window, Camera* camera, Scene* scene)
{
	glViewport(0, 0, window->getWidth(), window->getHeight());
	sceneShaderProgram->bind();
	mat4 projectionMat = transformation->getProjectionMatrix();
	sceneShaderProgram->setMat4Uniform("projectionMatrix", projectionMat, 1);

	mat4 orthoProjMatrix = transformation->getOrthoProjectionMatrix();
	sceneShaderProgram->setMat4Uniform("orthoProjectionMatrix", orthoProjMatrix, 1);

	mat4 viewMat = transformation->getViewMatrix();
	SceneLight* sceneLight = scene->getSceneLight();
	mat4 lightViewMatrix = transformation->getLightViewMatrix();
	renderLights(viewMat, sceneLight);
	
	sceneShaderProgram->setTextureUniform(0, "texture_sampler", GL_TEXTURE_2D);
	sceneShaderProgram->setTextureUniform(1, "normalMap", GL_TEXTURE_2D);
	sceneShaderProgram->setTextureUniform(2, "shadowMap", GL_TEXTURE_2D);
	sceneShaderProgram->setFogUniform("fog", scene->getFog());

	map<Mesh*, vector<GameItem*>> meshes = scene->getGameMeshes();
	for (auto iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		sceneShaderProgram->setMaterialUniform("material", iter->first->getMaterial());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, shadowMap->getDepthMapTexture()->id());

		iter->first->renderList(iter->second, [this, lightViewMatrix](GameItem* gameItem) {
			mat4 viewMat = transformation->getViewMatrix();
			mat4 modelViewMatrix = transformation->updateModelViewMatrix(gameItem, viewMat);
			sceneShaderProgram->setMat4Uniform("modelViewMatrix", modelViewMatrix, 1);
			mat4 modelLightViewMatrix = transformation->buildModelLightViewMatrix(gameItem, lightViewMatrix);
			sceneShaderProgram->setMat4Uniform("modelLightViewMatrix", modelLightViewMatrix, 1);
			});
	}
}

void Renderer::renderSkyBox(Window* window, Camera* camera, Scene* scene)
{
	skyBoxShaderProgram->bind();

	skyBoxShaderProgram->setTextureUniform(0, "texture_sampler", GL_TEXTURE_2D);

	mat4 projectionMatrix = transformation->getProjectionMatrix();
	skyBoxShaderProgram->setMat4Uniform("projectionMatrix", projectionMatrix, 1);
	SkyBox* skyBox = scene->getSkyBox();
	mat4 viewMatrix = transformation->getViewMatrix();
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
	mat4 modelViewMatrix = transformation->updateModelViewMatrix(skyBox, viewMatrix);
	skyBoxShaderProgram->setMat4Uniform("modelViewMatrix", modelViewMatrix, 1);
	skyBoxShaderProgram->setFloatUniform("ambientLight", &(scene->getSceneLight()->getAmbientLight()[0]), 3, 1);

	scene->getSkyBox()->getMesh()->render();

	skyBoxShaderProgram->unbind();
}

void Renderer::renderDepthMap(Window* window, Camera* camera, Scene* scene)
{
	if (!shadowMap)
		shadowMap = new ShadowMap();
	shadowMap->bind();
	shadowMap->init();

	depthShaderProgram->bind();

	DirectionalLight* directionalLight = scene->getSceneLight()->getDirectionalLight();
	vec3 lightDirection = directionalLight->getDirection();
	//float a = acos(lightDirection[2]);
	float lightAngleX = (float)radians(acos(lightDirection[0]));
	float lightAngleY = (float)radians(asin(lightDirection[1]));
	float lightAngleZ = 0;

	mat4 lightViewMatrix = transformation->updateLightViewMatrix(vec3(lightDirection * directionalLight->getShadowPosMult()), vec3(lightAngleX, lightAngleY, lightAngleZ));
	DirectionalLight::OrthoCoords orthCoords = directionalLight->getOrthoCoords();
	mat4 orthoProjMatrix = transformation->updateOrthoProjectionMatrix(orthCoords.left, orthCoords.right, orthCoords.bottom, orthCoords.top, orthCoords.near, orthCoords.far);
	depthShaderProgram->setMat4Uniform("orthoProjectionMatrix", orthoProjMatrix, 1);

	map<Mesh*, vector<GameItem*>> meshes = scene->getGameMeshes();
	for (auto iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		iter->first->renderList(iter->second, [this, lightViewMatrix](GameItem* gameItem) {
			mat4 modelLightViewMatrix = transformation->buildModelLightViewMatrix(gameItem, lightViewMatrix);
			depthShaderProgram->setMat4Uniform("modelLightViewMatrix", modelLightViewMatrix, 1);
			});
	}

	shadowMap->unbind();
}

void Renderer::setupSceneShader()
{
	sceneShaderProgram = new ShaderProgram(Utils::SysPath.ShaderPath + "test.vs", Utils::SysPath.ShaderPath + "test.fs");

	// Create uniforms for modelView and projection matrices and texture
	sceneShaderProgram->createUniform("projectionMatrix");
	sceneShaderProgram->createUniform("modelViewMatrix");
	sceneShaderProgram->createUniform("texture_sampler");
	sceneShaderProgram->createUniform("normalMap");
	// Create uniform for material
	sceneShaderProgram->createMaterialUniform("material");
	// Create lighting related uniforms
	sceneShaderProgram->createUniform("specularPower");
	sceneShaderProgram->createUniform("ambientLight");
	sceneShaderProgram->createPointLightUniform("pointLights", MAX_POINT_LIGHTS);
	sceneShaderProgram->createSpotLightUniform("spotLights", MAX_SPOT_LIGHTS);
	sceneShaderProgram->createDirectionalLightUniform("directionalLight");
	sceneShaderProgram->createFogUniform("fog");

	// Create uniforms for shadow mapping
	sceneShaderProgram->createUniform("shadowMap");
	sceneShaderProgram->createUniform("orthoProjectionMatrix");
	sceneShaderProgram->createUniform("modelLightViewMatrix");
}

void Renderer::setupSkyBoxShader()
{
	skyBoxShaderProgram = new ShaderProgram(Utils::SysPath.ShaderPath + "skybox.vs", Utils::SysPath.ShaderPath + "skybox.fs");

	// Create uniforms for projection matrix
	skyBoxShaderProgram->createUniform("projectionMatrix");
	skyBoxShaderProgram->createUniform("modelViewMatrix");
	skyBoxShaderProgram->createUniform("texture_sampler");
	skyBoxShaderProgram->createUniform("ambientLight");
}

void Renderer::setupDepthShader()
{
	depthShaderProgram = new ShaderProgram(Utils::SysPath.ShaderPath + "depth_vertext.vs", Utils::SysPath.ShaderPath + "depth_fragment.fs");

	depthShaderProgram->createUniform("orthoProjectionMatrix");
	depthShaderProgram->createUniform("modelLightViewMatrix");
}
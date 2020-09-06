#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "Transform.h"
#include "se_gl_component/ShaderProgram.h"
#include <se_aux/Window.h>
#include <se_game/Scene.h>
#include <vector>
class Renderer {
public:
	Renderer();
	~Renderer();
	void init(Window* window);
	void clear();
	void render(Window* window, Camera* camera, Scene* scene);
	void cleanup();
protected:
	virtual void renderLights(const mat4& viewMatrix, SceneLight* sceneLight);
	virtual void renderScene(Window* window, Camera* camera, Scene* scene);
	virtual void renderSkyBox(Window* window, Camera* camera, Scene* scene);
	virtual void setupSceneShader();
	virtual void setupSkyBoxShader();
private:
	static const int MAX_POINT_LIGHTS = 5;
	static const int MAX_SPOT_LIGHTS = 5;

	static float fov;
	static float zNear;
	static float zFar;
	Transform* transformation;
	ShaderProgram* sceneShaderProgram;
	ShaderProgram* skyBoxShaderProgram;
	float specularPower;
};
#endif

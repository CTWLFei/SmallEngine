#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "Transform.h"
#include "se_gl_component/ShaderProgram.h"
#include <se_aux/Window.h>
#include <vector>
class Renderer {
public:
	Renderer();
	~Renderer();
	void init(Window* window);
	void clear();
	void render(Window* window, Camera* camera, vector<GameItem*>& gameItems);
	void cleanup();
private:
	static float fov;
	static float zNear;
	static float zFar;
	Transform* transformation;
	ShaderProgram* shaderProgram;
};
#endif

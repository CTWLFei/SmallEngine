#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <vmath.h>
#include <se_core/se_camera/Camera.h>
#include <se_game/GameItem.h>
using namespace vmath;
class Transform {
public:
	Transform();
	~Transform() { }
	mat4 getProjectionMatrix();
	mat4 updateProjectionMatrix(float fov, float width, float height, float zNear, float zFar);
	mat4 getViewMatrix();
	mat4 updateViewMatrix(Camera& camera);
	mat4 updateModelViewMatrix(GameItem* gameItem, mat4& viewMatrixAux);
private:
	mat4 viewMatrix;
	mat4 modelViewMatrix;
	mat4 projectionMatrix;
};

#endif

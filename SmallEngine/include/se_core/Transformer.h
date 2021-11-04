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

	mat4 getModelViewMatrix();
	mat4 updateModelViewMatrix(GameItem* gameItem, mat4& viewMatrixAux);
	mat4 buildModelViewMatrix(GameItem* gameItem, mat4& matrix);

	mat4 getOrtho2DProjectionMatrix(float left, float right, float bottom, float top);

	mat4 getOrthoProjectionMatrix();
	mat4 updateOrthoProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
	mat4 buildOrtoProjModelMatrix(GameItem* gameItem, mat4& orthoMatrix);

	mat4 getLightViewMatrix();
	mat4 updateLightViewMatrix(vec3 position, vec3 rotation);
	mat4 buildModelLightViewMatrix(GameItem* gameItem, mat4 matrix);
	void setLightViewMatrix(mat4& lightViewMatrix);

	mat4 updateGenericViewMatrix(vec3 position, vec3 rotation, mat4& matrix);

private:
	mat4 viewMatrix;
	mat4 modelViewMatrix;
	mat4 modelMatrix;
	mat4 projectionMatrix;
	mat4 lightViewMatrix;
	mat4 modelLightMatrix;
	mat4 modelLightViewMatrix;
	mat4 orthoProjMatrix;
	mat4 ortho2DMatrix;
	mat4 orthoModelMatrix;
};

#endif

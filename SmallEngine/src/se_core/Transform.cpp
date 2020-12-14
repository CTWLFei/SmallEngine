#include <se_core/Transform.h>

Transform::Transform() 
{
	viewMatrix = mat4::identity();
	modelViewMatrix = mat4::identity();
	projectionMatrix = mat4::identity();
}

mat4 Transform::getProjectionMatrix()
{
	return this->projectionMatrix;
}

mat4 Transform::updateProjectionMatrix(float fov, float width, float height, float zNear, float zFar)
{
	this->projectionMatrix = perspective(fov, width / height, zNear, zFar);
	return this->projectionMatrix;
}

mat4 Transform::getViewMatrix()
{
	return viewMatrix;
}

mat4 Transform::updateViewMatrix(Camera& camera)
{
	vec3 cameraPos = camera.getPosition();
	vec3 rotation = camera.getRotation();
	// First do the rotation so camera rotates over its position
	mat4 rotateX = rotate(rotation[0], 1.0f, 0.0f, 0.0f);
	mat4 rotateY = rotate(rotation[1], 0.0f, 1.0f, 0.0f);
	mat4 rotateZ = rotate(rotation[2], 0.0f, 0.0f, 1.0f);
	viewMatrix = rotateX * rotateY * rotateZ;
	// Then do the translation
	viewMatrix = translate<float>(-cameraPos[0], -cameraPos[1], -cameraPos[2]) * viewMatrix;
	return viewMatrix;
}
mat4 Transform::updateModelViewMatrix(GameItem* gameItem, mat4& viewMatrixAux)
{
	vec3 rotation = gameItem->getRotation();
	modelMatrix = modelMatrix.identity();
	modelMatrix = translate<float>(gameItem->getPosition()[0], gameItem->getPosition()[1], gameItem->getPosition()[2]) * modelMatrix;
	mat4 rotateX = rotate(-rotation[0], 1.0f, 0.0f, 0.0f);
	mat4 rotateY = rotate(-rotation[1], 0.0f, 1.0f, 0.0f);
	mat4 rotateZ = rotate(-rotation[2], 0.0f, 0.0f, 1.0f);
	modelMatrix = modelMatrix * rotateX * rotateY * rotateZ * scale(gameItem->getScale());
	//LOGGER_WARN("modelMatrix's position is: x=" + to_string(viewMatrixAux[3][0]) + ";y=" + to_string(viewMatrixAux[3][1]) + ";z=" + to_string(viewMatrixAux[3][2]));
	return viewMatrixAux * modelMatrix;
}
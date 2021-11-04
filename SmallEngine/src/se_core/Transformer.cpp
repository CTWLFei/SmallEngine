#include <se_core/Transformer.h>

Transform::Transform() 
{
	viewMatrix = mat4::identity();
	modelViewMatrix = mat4::identity();
	projectionMatrix = mat4::identity();
	lightViewMatrix = mat4::identity();
	orthoProjMatrix = mat4::identity();
	ortho2DMatrix = mat4::identity();
	orthoModelMatrix = mat4::identity();
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
	//vec3 cameraPos = camera.getPosition();
	//vec3 rotation = camera.getRotation();
	//// First do the rotation so camera rotates over its position
	//mat4 rotateX = rotate(rotation[0], 1.0f, 0.0f, 0.0f);
	//mat4 rotateY = rotate(rotation[1], 0.0f, 1.0f, 0.0f);
	//mat4 rotateZ = rotate(rotation[2], 0.0f, 0.0f, 1.0f);
	//viewMatrix = rotateX * rotateY * rotateZ;
	//// Then do the translation
	//viewMatrix = viewMatrix * translate<float>(-cameraPos[0], -cameraPos[1], -cameraPos[2]);
	viewMatrix = camera.getViewMatrix();
	return viewMatrix;
}

mat4 Transform::getModelViewMatrix()
{
	return modelViewMatrix;
}

mat4 Transform::updateModelViewMatrix(GameItem* gameItem, mat4& viewMatrixAux)
{
	vec3 rotation = gameItem->getRotation();
	modelMatrix = modelMatrix.identity();
	modelMatrix = translate<float>(gameItem->getPosition()[0], gameItem->getPosition()[1], gameItem->getPosition()[2]) * modelMatrix;
	mat4 rotateX = rotate(-rotation[0], 1.0f, 0.0f, 0.0f);
	mat4 rotateY = rotate(-rotation[1], 0.0f, 1.0f, 0.0f);
	mat4 rotateZ = rotate(-rotation[2], 0.0f, 0.0f, 1.0f);
	vec3 itemScale = gameItem->getScale();
	modelMatrix = modelMatrix * rotateX * rotateY * rotateZ * scale(itemScale[0], itemScale[1], itemScale[2]);
	//LOGGER_WARN("modelMatrix's position is: x=" + to_string(viewMatrixAux[3][0]) + ";y=" + to_string(viewMatrixAux[3][1]) + ";z=" + to_string(viewMatrixAux[3][2]));
	return viewMatrixAux * modelMatrix;
}

mat4 Transform::getOrtho2DProjectionMatrix(float left, float right, float bottom, float top)
{
	ortho2DMatrix = vmath::orthogonal2D(left, right, bottom, top);
	return ortho2DMatrix;
}

mat4 Transform::getOrthoProjectionMatrix()
{
	return orthoProjMatrix;
}
mat4 Transform::updateOrthoProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
{
	orthoProjMatrix = orthogonal(left, right, bottom, top, zNear, zFar);
	return orthoProjMatrix;
}
mat4 Transform::buildOrtoProjModelMatrix(GameItem* gameItem, mat4& orthoMatrix)
{
	vec3 rotation = gameItem->getRotation();
	modelMatrix = modelMatrix.identity();
	modelMatrix = translate<float>(gameItem->getPosition()[0], gameItem->getPosition()[1], gameItem->getPosition()[2]) * modelMatrix;
	mat4 rotateX = rotate(-rotation[0], 1.0f, 0.0f, 0.0f);
	mat4 rotateY = rotate(-rotation[1], 0.0f, 1.0f, 0.0f);
	mat4 rotateZ = rotate(-rotation[2], 0.0f, 0.0f, 1.0f);
	vec3 itemScale = gameItem->getScale();
	modelMatrix = modelMatrix * rotateX * rotateY * rotateZ * scale(itemScale[0], itemScale[1], itemScale[2]);

	orthoModelMatrix = orthoMatrix * modelMatrix;

	return orthoModelMatrix;
}

mat4 Transform::getLightViewMatrix()
{
	return lightViewMatrix;
}
mat4 Transform::updateLightViewMatrix(vec3 position, vec3 rotation)
{
	return updateGenericViewMatrix(position, rotation, lightViewMatrix);
}
mat4 Transform::buildModelLightViewMatrix(GameItem* gameItem, mat4 matrix)
{
	vec3 rotation = gameItem->getRotation();
	modelLightMatrix = mat4::identity();
	modelLightMatrix = translate<float>(gameItem->getPosition()[0], gameItem->getPosition()[1], gameItem->getPosition()[2]) * modelLightMatrix;
	mat4 rotateX = rotate(-rotation[0], 1.0f, 0.0f, 0.0f);
	mat4 rotateY = rotate(-rotation[1], 0.0f, 1.0f, 0.0f);
	mat4 rotateZ = rotate(-rotation[2], 0.0f, 0.0f, 1.0f);
	vec3 itemScale = gameItem->getScale();
	modelLightMatrix = modelLightMatrix * rotateX * rotateY * rotateZ * scale(itemScale[0], itemScale[1], itemScale[2]);

	modelLightViewMatrix = matrix * modelLightMatrix;
	return modelLightViewMatrix;
}
void Transform::setLightViewMatrix(mat4& lightViewMatrix)
{
	this->lightViewMatrix = lightViewMatrix;
}

mat4 Transform::updateGenericViewMatrix(vec3 position, vec3 rotation, mat4& matrix)
{
	matrix = mat4::identity();

	mat4 translateMatrix = translate<float>(-position[0], -position[1], -position[2]);
	mat4 rotateX = rotate(-rotation[0], 1.0f, 0.0f, 0.0f);
	mat4 rotateY = rotate(-rotation[1], 0.0f, 1.0f, 0.0f);

	matrix = matrix * rotateX * rotateY * translateMatrix;
	return matrix;
}
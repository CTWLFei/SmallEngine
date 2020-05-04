#include <se_core/se_camera/Camera.h>
#include <math.h>
Camera::Camera()
{
	this->position = vec3(0);
	this->rotation = vec3(0);
}
Camera::Camera(vec3& position, vec3& rotation)
{
	this->position = position;
	this->rotation = rotation;
}
Camera::~Camera()
{

}

vec3 Camera::getPosition()
{
	return position;
}
void Camera::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}
void Camera::movePosition(float offsetX, float offsetY, float offsetZ)
{
	if (offsetZ != 0) {
		position[0] += (float)sin(rotation[1] / 180.0 * M_PI) * -1.0f * offsetZ;
		position[2] += (float)cos(rotation[1] / 180.0 * M_PI) * offsetZ;
	}
	if (offsetX != 0) {
		position[0] += (float)sin((rotation[1] - 90) / 180.0 * M_PI) * -1.0f * offsetX;
		position[2] += (float)cos((rotation[1] - 90) / 180.0 * M_PI) * offsetX;
	}
	position[1] += offsetY;
}
vec3 Camera::getRotation()
{
	return rotation;
}
void Camera::setRotation(float x, float y, float z)
{
	rotation[0] = x;
	rotation[1] = y;
	rotation[2] = z;
}
void Camera::moveRotation(float offsetX, float offsetY, float offsetZ)
{
	rotation[0] += offsetX;
	rotation[1] += offsetY;
	rotation[2] += offsetZ;
}
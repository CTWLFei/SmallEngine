#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <vmath.h>
using namespace vmath;
class Camera {
public:
	Camera();
	Camera(vec3& position, vec3& rotation);
	~Camera();

	vec3 getPosition();
	void setPosition(float x, float y, float z);
	void movePosition(float offsetX, float offsetY, float offsetZ);
	vec3 getRotation();
	void setRotation(float x, float y, float z);
	void moveRotation(float offsetX, float offsetY, float offsetZ);
private:
	vec3 position;
	vec3 rotation;
};

#endif

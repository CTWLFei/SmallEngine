#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <vmath.h>
using namespace vmath;
class Camera {
public:
	Camera();
	Camera(vec3 eye, vec3 target, vec3 up);
	~Camera();

	vec3 getPosition();
	void setPosition(float x, float y, float z);
	void movePosition(float offsetX, float offsetY, float offsetZ);
	void LookAt(vec3 target);
	vec3 getDirection();
	void Rotate(float x, float y, float z);

	virtual mat4 getViewMatrix();
	virtual mat4 getProjectionMatrix();

	virtual void UpdateViewMatrix();
	virtual void UpdateProjectionMatrix();
protected:
	vec3 LegitimateDirectionWithIncrement(vec3 direction, vec3 increment);
protected:
	vec3 m_eye;
	vec3 m_direction;
	vec3 m_up;
	vec3 m_target;
	
	mat4 m_viewMatrix;
	mat4 m_projectionMatrix;

	vec3 m_zaxis;		// The "forward" vector.
	vec3 m_xaxis;		// The "right" vector.
	vec3 m_yaxis;
};

#endif

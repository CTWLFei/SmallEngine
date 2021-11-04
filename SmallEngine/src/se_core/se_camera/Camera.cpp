#include <se_core/se_camera/Camera.h>
#include <math.h>
Camera::Camera()
{
	this->m_eye = vec3(-10, 0, 0);
	this->m_direction = vec3(1.0, 0.0, 0.0);
	this->m_up = vec3(0.0, 1.0, 0.0);
	UpdateViewMatrix();
}
Camera::Camera(vec3 eye, vec3 target, vec3 up)
{
	this->m_eye = eye;
	this->m_direction = vmath::normalize(target - eye);
	this->m_up = up;
}
Camera::~Camera()
{

}

vec3 Camera::getPosition()
{
	return m_eye;
}
void Camera::setPosition(float x, float y, float z)
{
	m_eye[0] = x;
	m_eye[1] = y;
	m_eye[2] = z;
}
void Camera::movePosition(float offsetX, float offsetY, float offsetZ)
{
	m_eye += m_xaxis * offsetX - m_zaxis * offsetZ + m_yaxis * offsetY;
	UpdateViewMatrix();
}

void Camera::LookAt(vec3 target)
{
	this->m_target = target;
	this->m_direction = vmath::normalize(target - this->m_eye);
	UpdateViewMatrix();
}

vec3 Camera::getDirection()
{
	return m_direction;
}

void Camera::Rotate(float x, float y, float z)
{
	mat4 rotateX = rotate(x, m_xaxis);
	mat4 rotateY = rotate(y, m_yaxis);
	mat4 rotateZ = rotate(z, m_zaxis);
	mat4 rotateMatrix = rotateX * rotateY * rotateZ;
	vec4 rotateVec = vec4(this->m_direction, 0.0) * rotateMatrix;
	this->m_direction = vec3(rotateVec[0], rotateVec[1], rotateVec[2]);
	this->m_target = m_eye + m_direction;
	UpdateViewMatrix();
}

mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

mat4 Camera::getProjectionMatrix()
{
	return mat4();
}

void Camera::UpdateViewMatrix()
{
	m_zaxis = vmath::normalize(m_direction);    // The "forward" vector.
	m_xaxis = vmath::normalize(cross(m_up, m_zaxis));// The "right" vector.
	m_yaxis = cross(m_zaxis, m_xaxis);     // The "up" vector.
	mat4 orientation = mat4(
		vec4(m_xaxis[0], m_yaxis[0], -m_zaxis[0], 0),
		vec4(m_xaxis[1], m_yaxis[1], -m_zaxis[1], 0),
		vec4(m_xaxis[2], m_yaxis[2], -m_zaxis[2], 0),
		vec4(0, 0, 0, 1)
	);

	mat4 translation = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-m_eye[0], -m_eye[1], -m_eye[2], 1)
	);

	//mat4 viewMat = vmath::lookat(m_eye, m_eye + m_direction, m_up);
	m_viewMatrix = orientation * translation;
	//m_viewMatrix = viewMat;
}
void Camera::UpdateProjectionMatrix()
{

}
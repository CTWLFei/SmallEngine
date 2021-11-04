#ifndef __DIRECTIONALIGHT_H__
#define __DIRECTIONALIGHT_H__

#include <vmath.h>
using namespace vmath;
class DirectionalLight {
public:
	class OrthoCoords {
	public:
		float left;
		float right;
		float bottom;
		float top;
		float near;
		float far;
	};

	DirectionalLight(vec3 color, vec3 direction, float intensity) {
		this->color = color;
		this->direction = direction;
		this->intensity = intensity;
		this->shadowPosMult = 1;
	}

	DirectionalLight(const DirectionalLight& light) {
		this->color = light.color;
		this->direction = light.direction;
		this->intensity = light.intensity;
		this->shadowPosMult = light.shadowPosMult;
	}

	vec3 getColor() {
		return color;
	}

	void setColor(vec3 color) {
		this->color = color;
	}

	vec3 getDirection() {
		return direction;
	}

	void setDirection(vec3 direction) {
		this->direction = direction;
	}

	float getIntensity() {
		return intensity;
	}

	void setIntensity(float intensity) {
		this->intensity = intensity;
	}

	float getShadowPosMult() {
		return this->shadowPosMult;
	}

	void setShadowPosMult(float shadowPosMult) {
		this->shadowPosMult = shadowPosMult;
	}

	OrthoCoords getOrthoCoords() {
		return this->orthoCords;
	}
	void setOrthoCords(float left, float right, float bottom, float top, float near, float far) {
		orthoCords.left = left;
		orthoCords.right = right;
		orthoCords.bottom = bottom;
		orthoCords.top = top;
		orthoCords.near = near;
		orthoCords.far = far;
	}

private:
	vec3 color;
	vec3 direction;
	float shadowPosMult;
	float intensity;
	OrthoCoords orthoCords;
};

#endif
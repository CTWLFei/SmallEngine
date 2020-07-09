#ifndef __DIRECTIONALIGHT_H__
#define __DIRECTIONALIGHT_H__

#include <vmath.h>
using namespace vmath;
class DirectionalLight {
public:
	DirectionalLight(vec3 color, vec3 direction, float intensity) {
		this->color = color;
		this->direction = direction;
		this->intensity = intensity;
	}

	DirectionalLight(const DirectionalLight& light) {
		this->color = light.color;
		this->direction = light.direction;
		this->intensity = light.intensity;
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
private:
	vec3 color;
	vec3 direction;
	float intensity;
};

#endif
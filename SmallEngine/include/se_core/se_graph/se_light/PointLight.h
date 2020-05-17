#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__
#include <vmath.h>
using namespace vmath;
class Attenuation {
public:
	Attenuation(float constant, float linear, float exponent) {
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}
	float getConstant() { return constant; }
	float getLinear() { return linear; }
	float getExponent() { return exponent; }
	void setConstant(float constant) { this->constant = constant; }
	void setLinear(float linear) { this->linear = linear; }
	void setExponent(float exponent) { this->exponent = exponent; }
private:
	float constant;
	float linear;
	float exponent;
};

class PointLight {
public:
	PointLight(vec3& color, vec3& position, float intensity) {
		this->color = color;
		this->position = position;
		this->intensity = intensity;
	}
	PointLight(vec3& color, vec3& position, float intensity, Attenuation* attenuation)
	{
		this->color = color;
		this->position = position;
		this->intensity = intensity;
		this->attenuation = attenuation;
	}
	PointLight(const PointLight& pointLight)
	{
		this->color = pointLight.color;
		this->position = pointLight.position;
		this->intensity = pointLight.intensity;
		this->attenuation = pointLight.attenuation;
	}

	vec3 getColor() {
		return color;
	}

	void setColor(vec3& color) {
		this->color = color;
	}

	vec3 getPosition() {
		return position;
	}

	void setPosition(vec3& position) {
		this->position = position;
	}

	float getIntensity() {
		return intensity;
	}

	void setIntensity(float intensity) {
		this->intensity = intensity;
	}

	Attenuation* getAttenuation() {
		return this->attenuation;
	}

	void setAttenuation(Attenuation* attenuation) {
		this->attenuation = attenuation;
	}
private:
	vec3 color;
	vec3 position;
	float intensity;
	Attenuation* attenuation;
};

#endif